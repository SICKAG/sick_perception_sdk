/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpsClient.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClientBase.hpp>

#include <csignal>
#include <cstdint>
#include <string>

namespace sick::httplib_client {

namespace {

/**
 * @brief Sets up SIGPIPE handling for SSL connections.
 * 
 * According to httplib documentation:
 * "When using SSL, it seems impossible to avoid SIGPIPE in all cases, since on some operating
 * systems, SIGPIPE can only be suppressed on a per-message basis, but there is no way to make
 * the OpenSSL library do so for its internal communications."
 * 
 * This function sets up a signal handler to ignore SIGPIPE on platforms where it is defined (Linux/Unix).
 * On platforms where SIGPIPE is not available (Windows, some embedded systems), this function does nothing.
 * 
 * If a SIGPIPE handler is already registered (i.e., not SIG_DFL), it will not be overridden to avoid
 * interfering with existing signal handling in the application.
 */
void setupSigpipeHandling()
{
#ifdef SIGPIPE
  // Set SIGPIPE handler to SIG_IGN and get the previous handler
  auto const previousHandler = std::signal(SIGPIPE, SIG_IGN);
  if (previousHandler == SIG_ERR)
  {
    // Failed to set signal handler
    return;
  }
  if (previousHandler != SIG_DFL)
  {
    // Handler was already set by something else, restore the previous handler
    if (std::signal(SIGPIPE, previousHandler) == SIG_ERR)
    {
      // Failed to restore previous handler, nothing we can do.
      LOG_WARNING("HttpsClient") << "Failed to restore previous SIGPIPE handler after setting it to SIG_IGN.";
    }
  }
#endif
}

} // namespace

HttpsClient::HttpsClient(IpV4Address address, std::uint16_t port)
  : HttpClientBase(address.toString(), port)
{
  setupSigpipeHandling();
}

HttpsClient::HttpsClient(IpV4Address address, std::uint16_t port, std::string const& caCertificatePath)
  : HttpsClient(address, port)
{
  m_client->set_ca_cert_path(caCertificatePath);
}

void HttpsClient::disableServerCertificateVerification()
{
  m_client->enable_server_certificate_verification(false);
}

void HttpsClient::disableServerHostnameVerification()
{
  m_client->enable_server_hostname_verification(false);
}

} // namespace sick::httplib_client
