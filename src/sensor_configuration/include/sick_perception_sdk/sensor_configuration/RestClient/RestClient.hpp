/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/RestClient/PostRequest.hpp>
#include <sick_perception_sdk/sensor_configuration/api/ResponseHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/json/Json.hpp>

#include <cstdint>
#include <string>

namespace sick {

/**
 * @brief REST client to handle the structure of REST requests to a SICK sensor.
 */
class SDK_EXPORT RestClient
{
public:
  explicit RestClient(std::shared_ptr<IHttpClient> httpClient);

  /**
   * @brief Perform a GET request to the device where the response is wrapped inside a `data` object.
   *
   * The REST call will be addressed to the endpoint `/api/<variableName>`.
   *
   * The response for is expected to be of the form:
   *
   * ```json
   * {
   *   "header": {
   *     "status": <statusCode>,
   *     "message": "<statusMessage>"
   *   },
   *   "data": {
   *     "<variableName>": {
   *       ...
   *     }
   *   }
   * }
   * ```
   *
   * @throws std::invalid_operation The function will throw an exception if the `statusCode` of the `header` object of
   * the response body is not 0.
   *
   * @return The deserialized data of the `variableName` object of the response body.
   */
  template <class ReturnT>
  auto get(std::string const& variableName) const -> ReturnT
  {
    return get<ReturnT>(variableName, variableName);
  }

  /**
   * @brief Perform a GET request to a variable that contains only one field called `fieldName`.
   *
   * The REST call will be addressed to the endpoint `/api/<variableName>`.
   *
   * If `withDataField` = true the device response is expected to be of the form:
   *
   * ```json
   * {
   *   "header": {
   *     "status": <statusCode>,
   *     "message": "<statusMessage>"
   *   },
   *   "<fieldName>": {
   *     ...
   *   }
   * }
   * ```
   *
   * Otherwise the response is expected to be of the form:
   *
   * ```json
   * {
   *   "header": {
   *     "status": <statusCode>,
   *     "message": "<statusMessage>"
   *   },
   *   "data": {
   *     "<fieldName>": {
   *       ...
   *     }
   *   }
   * }
   * ```
   *
   * @throws std::invalid_operation The function will throw an exception if the `statusCode` of the `header` object of
   * the response body is not 0.
   *
   * @return The deserialized data of the `variableName` object of the response body.
   */
  template <class ReturnT>
  auto get(std::string const& variableName, std::string const& fieldName, bool withDataField = true) const -> ReturnT
  {
    std::string const endpoint = "/api/" + variableName;

    // AXIVION Next Line CertC++-EXP34: false positive, m_httpClient is checked for nullptr in the constructor and cannot be changed afterwards.
    auto const responseJson = m_httpClient->get(endpoint);

    // Verify that the response header indicates success before trying to deserializing the whole response.
    auto const header = json::deserialize<ResponseHeader>(responseJson, "header", false);
    if (header.status != 0)
    {
      throw std::runtime_error("Device GET request failed: " + header.message);
    }

    // Now we can try to deserialize the full response.
    auto const response = json::deserialize<ReturnT>(responseJson, fieldName, withDataField);
    return response;
  }

  /**
   * Start a POST request.
   *
   * For details see @a PostRequest.
   */
  auto post(std::string const& variableName) const -> PostRequest;

private:
  std::shared_ptr<IHttpClient> m_httpClient;
};

} // namespace sick
