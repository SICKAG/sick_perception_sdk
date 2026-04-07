/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/RestClient/PostRequest.hpp>

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/ResponseHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/json/Json.hpp>

#include <memory>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace sick {

PostRequest::PostRequest(std::string variableName, std::shared_ptr<IHttpClient> httpClient)
  : m_variableName(std::move(variableName))
  , m_httpClient(std::move(httpClient))
  , m_requestJson(std::nullopt)
{
  if (m_httpClient == nullptr)
  {
    throw std::invalid_argument("HttpClient cannot be null");
  }
}

auto PostRequest::execute() -> PostRequest const&
{
  std::string const endpoint = "/api/" + m_variableName;

  auto requestJson = [this]() -> nlohmann::ordered_json {
    if (m_authenticationHeader.has_value())
    {
      nlohmann::ordered_json json {{"header", *m_authenticationHeader}};
      if (m_requestJson.has_value())
      {
        // Merge the header and payload to keep the order of header first and then the payload.
        // That's important for the SOPAS REST API.
        json.update(*m_requestJson);
      }
      return json;
    }

    if (m_requestJson.has_value())
    {
      return *m_requestJson;
    }

    // This case happens if there is no request payload.
    return nlohmann::ordered_json {};
  }();

  std::string const requestJsonStr = requestJson.dump();
  // AXIVION Next Line CertC++-EXP34: false positive, m_httpClient is checked for nullptr in the constructor and cannot be changed afterwards.
  m_responseJson = m_httpClient->post(endpoint, requestJsonStr);

  // Verify that the response header indicates success before trying to deserializing the whole response.
  // Therefore we just deserialize an `EmptyResponse` here. After execute() returns the caller can call
  // `withResponse<...>` to get the actual payload.
  auto const header = json::deserialize<ResponseHeader>(m_responseJson, "header", false);
  if (header.status != 0)
  {
    throw std::runtime_error("Device POST request failed with status " + std::to_string(header.status) + ": " + header.message);
  }

  return *this;
}

auto PostRequest::withAuthentication(AuthenticationHeader const& header) -> PostRequest&
{
  m_authenticationHeader = header;
  return *this;
}

auto PostRequest::withoutAuthentication() -> PostRequest&
{
  // This function is empty and only used as a marker by our callers.
  return *this;
}

auto PostRequest::withoutRequestPayload() -> PostRequest&
{
  // This function is empty and only used as a marker by our callers.
  return *this;
}

} // namespace sick
