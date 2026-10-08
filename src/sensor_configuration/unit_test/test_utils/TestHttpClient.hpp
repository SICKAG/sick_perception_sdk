/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <deque>
#include <string>
#include <vector>

namespace sick::test {

/**
 * @brief In-memory `IHttpClient` mock.
 *
 * Records every @a HttpRequest that is sent and answers with responses queued in FIFO order. This
 * lets tests exercise the SOPAS envelope, authentication and session-token logic without a device.
 * 
 * @ingroup Http
 */
class TestHttpClient : public sick::IHttpClient
{
public:
  TestHttpClient()           = default;
  ~TestHttpClient() override = default;

  auto send(HttpRequest const& request) const -> HttpResponse override;

  /**
   * @brief Queue a `200 OK` `application/json` response with the given body.
   */
  void queueJsonResponse(std::string body) const;

  /**
   * @brief Queue a response with an explicit status code and (optional) body.
   */
  void queueResponse(int statusCode, std::string body = "", std::string contentType = "application/json") const;

  mutable std::vector<HttpRequest> requests;
  mutable std::deque<HttpResponse> responses;
};

} // namespace sick::test
