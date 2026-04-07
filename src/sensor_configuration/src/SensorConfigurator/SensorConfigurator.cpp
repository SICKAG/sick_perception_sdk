/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/SensorConfigurator.hpp>

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/RestClient/PostRequest.hpp>
#include <sick_perception_sdk/sensor_configuration/RestClient/RestClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Challenge.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <array>
#include <iomanip>
#include <ios>
#include <memory>
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
  EVP_MD_CTX* ctx = EVP_MD_CTX_new();
  if (ctx == nullptr)
  {
    throw std::runtime_error("EVP_MD_CTX_new failed");
  }
  if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1)
  {
    EVP_MD_CTX_free(ctx);
    throw std::runtime_error("EVP_DigestInit_ex failed");
  }
  if (EVP_DigestUpdate(ctx, str.c_str(), str.size()) != 1)
  {
    EVP_MD_CTX_free(ctx);
    throw std::runtime_error("EVP_DigestUpdate failed");
  }
  unsigned int hashLength = 0;
  if (EVP_DigestFinal_ex(ctx, hash.data(), &hashLength) != 1)
  {
    EVP_MD_CTX_free(ctx);
    throw std::runtime_error("EVP_DigestFinal_ex failed");
  }
  if (hashLength > hash.size())
  {
    throw std::runtime_error("EVP_DigestFinal_ex returned too many hash bytes");
  }
  EVP_MD_CTX_free(ctx);

  std::stringstream stream;
  for (unsigned int i = 0; i < hashLength; i++)
  {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index): index limit is given by EVP_DigestFinal_ex
    stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
  }
  return stream.str();
}

} // namespace

SensorConfigurator::SensorConfigurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : m_client(std::move(httpClient))
  , m_userLevelStr(UserLevelToStringMap.at(userLevel))
  , m_password(std::move(password))
{ }

auto SensorConfigurator::post(std::string const& endpoint) const -> PostRequest
{
  return m_client.post(endpoint).withAuthentication(getAuthenticationHeader(endpoint, getChallenge()));
}

auto SensorConfigurator::getChallenge() const -> Challenge
{
  auto const challenge =
    m_client.post("getChallenge").withoutAuthentication().withRequestPayload("user", m_userLevelStr).execute().withPlainResponsePayload<Challenge>("challenge");
  return challenge;
}

auto SensorConfigurator::getAuthenticationHeader(std::string const& variableName, Challenge const& challenge) const -> AuthenticationHeader
{
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

  std::string const request2 = "POST:" + variableName;
  std::string const hash2    = sha256(request2);

  std::string const request3 = hash1 + ":" + challenge.nonce + ":" + hash2;
  std::string const response = sha256(request3);

  AuthenticationHeader header {challenge.nonce, challenge.opaque, challenge.realm, response, m_userLevelStr};
  return header;
}

} // namespace sick
