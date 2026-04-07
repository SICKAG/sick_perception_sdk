/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClientBase.hpp>

#include <cstdint>
#include <httplib.h>
#include <string>

namespace sick::httplib_client {

/**
 * @brief HTTP client implementation using [httplib](https://github.com/yhirose/cpp-httplib).
 */
class SDK_EXPORT HttpClient final : public HttpClientBase<httplib::Client>
{
public:
  explicit HttpClient(IpV4Address address, std::uint16_t port);

  ~HttpClient() override = default;

  HttpClient(HttpClient const&)                        = delete;
  auto operator=(HttpClient const&) -> HttpClient&     = delete;
  HttpClient(HttpClient&&) noexcept                    = delete;
  auto operator=(HttpClient&&) noexcept -> HttpClient& = delete;
};

} // namespace sick::httplib_client
