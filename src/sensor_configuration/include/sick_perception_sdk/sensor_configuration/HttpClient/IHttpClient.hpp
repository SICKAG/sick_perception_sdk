/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <string>

namespace sick {

/**
 * @brief Interface for an HTTP client to perform GET and POST requests.
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
   * @brief Perform an HTTP GET request to the specified endpoint and return the response body.
   */
  virtual auto get(std::string const& endpoint) const -> std::string = 0;

  /**
   * @brief Perform an HTTP POST request to the specified endpoint with the given payload and return the response body.
   */
  virtual auto post(std::string const& endpoint, std::string const& payload) const -> std::string = 0;
};

} // namespace sick
