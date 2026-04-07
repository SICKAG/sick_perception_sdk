/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/json/Json.hpp>

#include <optional>
#include <string>

namespace sick {

class SDK_EXPORT PostRequest
{
public:
  /**
   * @brief Helper to build and execute a POST request.
   *
   * The REST call will be addressed to the endpoint `/api/<variableName>`.
   *
   * The class is set up with call chaining in mind. A successful execution requires the following call sequence:
   *
   * 1. set authentication mode (@a withAuthentication() or @a withoutAuthentication()),
   * 2. set request payload (@a withRequestPayload() or @a withoutRequestPayload()),
   * 3. execute the request (@a execute()),
   * 4. [optional] get the response payload (@a withResponsePayloadInData(), @a withPlainResponsePayload()).
   */
  explicit PostRequest(std::string variableName, std::shared_ptr<IHttpClient> httpClient);

  /**
   * @brief Execute the POST request.
   *
   * For this function, the response for the endpoint `/api/<variableName>` is expected to be of the form:
   *
   * ```json
   * {
   *   "header": {
   *     "status": <statusCode>,
   *     "message": "<statusMessage>"
   *   },
   *   ...
   * }
   * ```
   *
   * @throws std::invalid_operation The function will throw an exception if the `statusCode` of the `header` object of
   * the response body is not 0.
   *
   * @return own reference for call chaining.
   */
  auto execute() -> PostRequest const&;

  // Function to specify the authentication header of the request.
  auto withAuthentication(AuthenticationHeader const& header) -> PostRequest&;
  auto withoutAuthentication() -> PostRequest&;

  // Functions to specify the body of the request.
  auto withoutRequestPayload() -> PostRequest&;

  template <typename ValueT>
  auto withPlainRequestPayload(ValueT value) -> PostRequest&
  {
    m_requestJson = nlohmann::ordered_json {{"data", value}};
    return *this;
  }

  template <typename ValueT>
  auto withRequestPayload(std::string const& fieldName, ValueT value) -> PostRequest&
  {
    m_requestJson = nlohmann::ordered_json {{"data", {{fieldName, value}}}};
    return *this;
  }

  // Functions to specify the response of the request.
  /**
   * @brief Fetch the response payload that is wrapped inside a `data` field.
   *
   * The response is expected to be of the form:
   *
   * ```json
   * {
   *   ...,
   *   "data": {
   *     "<fieldName>": {
   *       ...
   *     }
   *   }
   * }
   * ```
   */
  template <class ReturnT>
  auto withResponsePayloadInData(std::string const& fieldName) const -> ReturnT
  {
    return json::deserialize<ReturnT>(m_responseJson, fieldName);
  }

  /**
   * @brief Fetch the response payload directly, without looking for a `data` field around it.
   *
   * The response is expected to be of the form:
   *
   * ```json
   * {
   *   ...,
   *   "<fieldName>": {
   *     ...
   *   }
   * }
   * ```
   */
  template <class ReturnT>
  auto withPlainResponsePayload(std::string const& fieldName) const -> ReturnT
  {
    return json::deserialize<ReturnT>(m_responseJson, fieldName, false);
  }

  template <class ReturnT>
  auto withPlainResponsePayload() const -> ReturnT
  {
    return nlohmann::json::parse(m_responseJson).at("data").get<ReturnT>();
  }

private:
  std::string m_variableName;
  std::shared_ptr<IHttpClient> m_httpClient;
  std::optional<AuthenticationHeader> m_authenticationHeader;
  std::optional<nlohmann::ordered_json> m_requestJson;
  std::string m_responseJson;
};

} // namespace sick
