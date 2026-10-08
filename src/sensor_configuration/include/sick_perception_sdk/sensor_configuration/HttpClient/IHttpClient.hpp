/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <string>
#include <utility>
#include <vector>

namespace sick {

/** @defgroup Http HTTP Client
 * 
 * @brief HTTP request handling for sensor configuration
 * 
 * The sensor_configuration library uses an HTTP client to communicate with the sensor's REST API. The client is abstracted behind the 
 * `IHttpClient` interface so that different implementations can be used (e.g. for testing or to use a different HTTP library).
 * 
 * By default, the sick_perception_sdk provides an implementation based on [httplib](https://github.com/yhirose/cpp-httplib); 
 * see `sick::httplib_client::HttpClientBase`.
 *
*/

/**
 * @brief HTTP verbs used by the SICK sensor REST API.
 * 
 * @ingroup Http
 * @ingroup sensor_configuration
 */
enum class HttpMethod
{
  Get,
  Post,
  Put,
};

/**
 * @brief A content-type-aware HTTP request.
 *
 * The request carries raw bytes in @a body so both JSON and binary payloads (for the Class 4
 * PUT/binary endpoints) can be expressed. Additional headers (e.g. `X-Session-Token`) can be
 * supplied via @a headers.
 * 
 * @ingroup Http
 * @ingroup sensor_configuration
 */
struct HttpRequest
{
  HttpMethod method = HttpMethod::Get;                      ///< HTTP verb.
  std::string path;                                         ///< Request path, e.g. "/api/EtherIPAddress".
  std::string contentType = "application/json";             ///< Content type of the request body.
  std::string body;                                         ///< Raw request body (may be binary).
  std::vector<std::pair<std::string, std::string>> headers; ///< Extra request headers.
};

/**
 * @brief A content-type-aware HTTP response.
 * 
 * @ingroup Http
 * @ingroup sensor_configuration
 */
struct HttpResponse
{
  int statusCode = 0;      ///< Real HTTP status code (200 for the JSON endpoints).
  std::string contentType; ///< Content type of the response body.
  std::string body;        ///< Raw response body (may be binary).
};

/**
 * @brief Interface for an HTTP client used by the sensor configuration library.
 *
 * A single content-type-aware operation is exposed so that GET, POST, and PUT requests as well as
 * binary payloads can be handled uniformly. Implementations may wrap any HTTP library.
 * 
 * @ingroup Http
 * @ingroup sensor_configuration
 */
class SDK_EXPORT IHttpClient
{
public:
  IHttpClient()          = default;
  virtual ~IHttpClient() = default;

  IHttpClient(IHttpClient const&)                    = delete;
  auto operator=(IHttpClient const&) -> IHttpClient& = delete;
  IHttpClient(IHttpClient&&)                         = delete;
  auto operator=(IHttpClient&&) -> IHttpClient&      = delete;

  /**
   * @brief Perform an HTTP request and return the response.
   */
  virtual auto send(HttpRequest const& request) const -> HttpResponse = 0;
};

} // namespace sick
