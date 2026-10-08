/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Challenge.hpp>
#include <sick_perception_sdk/sensor_configuration/api/ResponseHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
// NOLINTNEXTLINE(misc-include-cleaner): false positive, header is required for JSON serialization.
#include <sick_perception_sdk/sensor_configuration/api/json/Json.hpp>

#include <array>
#include <iomanip>
#include <ios>
#include <memory>
#include <nlohmann/json.hpp>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/types.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace sick {

namespace {

auto sha256(std::string const& str) -> std::string
{
  std::array<unsigned char, SHA256_DIGEST_LENGTH> hash {};
  std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> const ctx(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
  if (ctx == nullptr)
  {
    throw std::runtime_error("EVP_MD_CTX_new failed");
  }
  if (EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1)
  {
    throw std::runtime_error("EVP_DigestInit_ex failed");
  }
  if (EVP_DigestUpdate(ctx.get(), str.c_str(), str.size()) != 1)
  {
    throw std::runtime_error("EVP_DigestUpdate failed");
  }
  unsigned int hashLength = 0;
  if (EVP_DigestFinal_ex(ctx.get(), hash.data(), &hashLength) != 1)
  {
    throw std::runtime_error("EVP_DigestFinal_ex failed");
  }
  if (hashLength > hash.size())
  {
    throw std::runtime_error("EVP_DigestFinal_ex returned too many hash bytes");
  }

  std::stringstream stream;
  for (unsigned int i = 0; i < hashLength; i++)
  {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index,cppcoreguidelines-pro-bounds-avoid-unchecked-container-access): index limit is given by EVP_DigestFinal_ex
    stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return stream.str();
}

} // namespace

SopasClient::SopasClient(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : m_httpClient(std::move(httpClient))
  , m_userLevelStr(toString(userLevel))
  , m_password(std::move(password))
{
  if (m_httpClient == nullptr)
  {
    throw std::invalid_argument("HttpClient cannot be null");
  }
}

auto SopasClient::sendRaw(HttpRequest const& request) const -> HttpResponse
{
  // AXIVION Next Line CertC++-EXP34: data pointer of request is checked in ctor
  return m_httpClient->send(request);
}

namespace {

// NOLINTNEXTLINE(misc-include-cleaner): nlohmann::json is provided by nlohmann/json.hpp
void throwIfError(nlohmann::json const& json)
{
  auto const header = json.at("header").get<ResponseHeader>();
  if (header.status != 0)
  {
    throw std::runtime_error("Device request failed with status " + std::to_string(header.status) + ": " + header.message);
  }
}

} // namespace

auto SopasClient::sendJsonGet(std::string const& path) const -> std::string
{
  HttpRequest request;
  request.method = HttpMethod::Get;
  request.path   = path;

  // AXIVION Next Line CertC++-EXP34: data pointer of request is checked in ctor
  auto const response = m_httpClient->send(request);
  throwIfError(nlohmann::json::parse(response.body));
  return response.body;
}

auto SopasClient::sendJsonPost(std::string const& path, std::string const& body) const -> std::string
{
  HttpRequest request;
  request.method      = HttpMethod::Post;
  request.path        = path;
  request.contentType = "application/json";
  request.body        = body;

  // AXIVION Next Line CertC++-EXP34: data pointer of request is checked in ctor
  auto const response = m_httpClient->send(request);
  throwIfError(nlohmann::json::parse(response.body));
  return response.body;
}

auto SopasClient::getChallenge() const -> Challenge
{
  // NOLINTNEXTLINE(misc-include-cleaner): nlohmann::ordered_json is provided by nlohmann/json.hpp
  nlohmann::ordered_json body;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access): nlohmann::json operator[] creates missing keys
  body["data"]["user"] = m_userLevelStr;

  auto const responseBody = sendJsonPost("/api/getChallenge", body.dump());
  return nlohmann::json::parse(responseBody).at("challenge").get<Challenge>();
}

auto SopasClient::authenticate(std::string const& endpointName) const -> AuthenticationHeader
{
  auto const challenge = getChallenge();

  auto const request1 = [this, &challenge]() -> std::string {
    std::string start = m_userLevelStr + ":" + challenge.realm + ":" + m_password;
    if (challenge.salt.empty())
    {
      return start;
    }

    // AXIVION Next Construct CertC++-STR51: data pointer of salt is checked above
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast): the REST API requires this behavior
    auto const saltStr = std::string(reinterpret_cast<char const*>(challenge.salt.data()), challenge.salt.size());
    return start + ":" + saltStr;
  }();
  std::string const hash1 = sha256(request1);

  std::string const request2 = "POST:" + endpointName;
  std::string const hash2    = sha256(request2);

  std::string const request3 = hash1 + ":" + challenge.nonce + ":" + hash2;
  std::string const response = sha256(request3);

  return AuthenticationHeader {challenge.nonce, challenge.opaque, challenge.realm, response, m_userLevelStr};
}

auto SopasClient::createSessionToken() const -> std::string
{
  nlohmann::ordered_json body;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access): nlohmann::json operator[] creates missing keys
  body["header"] = authenticate("CreateSessionToken");

  auto const responseBody = sendJsonPost("/api/CreateSessionToken", body.dump());
  return nlohmann::json::parse(responseBody).at("data").at("token").get<std::string>();
}

} // namespace sick
