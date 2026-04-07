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
 * @brief HTTPS client implementation using [httplib](https://github.com/yhirose/cpp-httplib).
 */
class SDK_EXPORT HttpsClient final : public HttpClientBase<httplib::SSLClient>
{
public:
  /**
 * @brief Construct an HTTPS client without explicit CA certificate for server certificate verification.
 * 
 * The client will try to use the system's default CA certificates.
 */
  explicit HttpsClient(IpV4Address address, std::uint16_t port);

  /**
 * @brief Construct an HTTPS client with an explicit CA certificate for server certificate verification.
 */
  explicit HttpsClient(IpV4Address address, std::uint16_t port, std::string const& caCertificatePath);
  ~HttpsClient() override = default;

  HttpsClient(HttpsClient const&)                        = delete;
  auto operator=(HttpsClient const&) -> HttpsClient&     = delete;
  HttpsClient(HttpsClient&&) noexcept                    = delete;
  auto operator=(HttpsClient&&) noexcept -> HttpsClient& = delete;

  /**
   * @brief Disable server certificate and hostname verification.
   * 
   * Certificate verification is enabled by default. It can be disabled if desired. Use with caution, 
   * as this makes the connection vulnerable to man-in-the-middle attacks.
   */
  void disableServerCertificateVerification();

  /**
   * @brief Disable server hostname verification.
   * 
   * Hostname verification is enabled by default. It can be disabled if desired. Use with caution, 
   * as this makes the connection vulnerable to man-in-the-middle attacks.
   */
  void disableServerHostnameVerification();
};

} // namespace sick::httplib_client
