/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/RestClient/RestClient.hpp>

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/RestClient/PostRequest.hpp>

#include <memory>
#include <string>
#include <utility>

namespace sick {

RestClient::RestClient(std::shared_ptr<IHttpClient> httpClient)
  : m_httpClient(std::move(httpClient))
{
  if (m_httpClient == nullptr)
  {
    throw std::invalid_argument("HttpClient cannot be null");
  }
}

auto RestClient::post(std::string const& variableName) const -> PostRequest
{
  return PostRequest(variableName, m_httpClient);
}

} // namespace sick
