/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Challenge.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <memory>
#include <string>

namespace sick {

/**
 * @brief The single home of the SICK REST conventions.
 *
 * `SopasClient` is the one place that knows how the SICK REST API deviates from ordinary REST:
 *
 * - the `data` / `<variableName>` envelope wrapping,
 * - logical errors are reported inside a `200 OK` body via `header.status`,
 * - proprietary challenge/response authentication for mutating requests,
 * - session-token acquisition for some endpoints.
 *
 * Generated `Endpoints` classes call the typed primitives below. Undocumented endpoints can be reached through the
 * raw escape hatch @a sendRaw().
 *
 * @note This public header is deliberately free of `nlohmann/json`. The typed template primitives
 * are only *declared* here and *defined* in `SopasClientImpl.hpp`, which is included solely by the
 * generated `Endpoints.g.cpp` files. Consumers therefore never pull in `nlohmann/json`.
 * 
 * @ingroup sensor_configuration
 */
class SDK_EXPORT SopasClient
{
public:
  /**
   * @brief Construct a SOPAS client.
   *
   * @param userLevel User level used for challenge/response authentication of mutating requests.
   * @param password Password used for challenge/response authentication of mutating requests.
   */
  SopasClient(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);

  auto httpClient() const -> IHttpClient const&
  {
    return *m_httpClient;
  }

  /**
   * @brief Read a variable via `GET /api/<variableName>`.
   *
   * The value is unwrapped from `data.<variableName>` after verifying `header.status == 0`.
   */
  template <class EndpointT>
  auto readVariable() const -> typename EndpointT::Get::Response;

  /**
   * @brief Write a variable via `POST /api/<variableName>`.
   *
   * The payload is wrapped under `data.<variableName>` and sent with a challenge/response header.
   */
  template <class EndpointT>
  void writeVariable(typename EndpointT::Post::Request const& payload) const;

  /**
   * @brief Invoke a method that has a request and a response payload.
   *
   * The request parameters are placed flat under `data`; the response is unwrapped from `data`.
   */
  template <class EndpointT>
  auto invokeMethod(typename EndpointT::Post::Request const& payload) const -> typename EndpointT::Post::Response;

  /**
   * @brief Invoke a method that has a request payload but no response payload.
   */
  template <class EndpointT>
  void invokeMethodWithoutResponse(typename EndpointT::Post::Request const& payload) const;

  /**
   * @brief Invoke a method that has no request payload but a response payload.
   */
  template <class EndpointT>
  auto invokeMethodWithoutRequest() const -> typename EndpointT::Post::Response;

  /**
   * @brief Invoke a method that has neither a request nor a response payload.
   */
  template <class EndpointT>
  void invokeMethodWithoutRequestAndResponse() const;

  /**
   * @brief Acquire a session token via `POST /api/CreateSessionToken` (returned in `data.token`).
   */
  auto createSessionToken() const -> std::string;

  /**
   * @brief Build a challenge/response authentication header for the given endpoint.
   *
   * Performs a `POST /api/getChallenge` round trip and computes the response hash chain.
   */
  auto authenticate(std::string const& endpointName) const -> AuthenticationHeader;

  /**
   * @brief Raw escape hatch for undocumented endpoints. No envelope handling is performed.
   */
  auto sendRaw(HttpRequest const& request) const -> HttpResponse;

private:
  // JSON plumbing kept out of the public header. These helpers send a request, verify that
  // `header.status == 0`, and return the raw (validated) response body. The typed template
  // primitives above (defined in SopasClientImpl.hpp) parse the returned body themselves.
  auto sendJsonGet(std::string const& path) const -> std::string;
  auto sendJsonPost(std::string const& path, std::string const& body) const -> std::string;
  auto getChallenge() const -> Challenge;

  std::shared_ptr<IHttpClient> m_httpClient;
  std::string m_userLevelStr;
  std::string m_password;
};

} // namespace sick
