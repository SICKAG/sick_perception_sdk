/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <httplib.h>

#include <chrono>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace sick::httplib_client {

/**
 * @brief Base class for HTTP clients using [httplib](https://github.com/yhirose/cpp-httplib).
 * 
 * @ingroup Http
 * @ingroup sensor_configuration
 */
template <class ClientT>
class HttpClientBase : public IHttpClient
{
public:
  template <typename... Args>
  explicit HttpClientBase(Args&&... args)
    : m_client(std::make_unique<ClientT>(std::forward<Args>(args)...))
  {
    auto const startTime = std::chrono::steady_clock::now();
    m_client->set_logger([startTime](httplib::Request const& req, httplib::Response const& res) -> void {
      auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
      LOG_FAST_LOOP_INFO("HttpClient") << "OK: " << req.method << " " << req.path << " -> " << res.status << " (" << res.body.size() << " bytes, " << duration
                                       << "ms)";
    });

    enableErrorLogging();
  }

  ~HttpClientBase() override = default;

  HttpClientBase(HttpClientBase const&)                        = delete;
  auto operator=(HttpClientBase const&) -> HttpClientBase&     = delete;
  HttpClientBase(HttpClientBase&&) noexcept                    = delete;
  auto operator=(HttpClientBase&&) noexcept -> HttpClientBase& = delete;

  auto get(std::string const& endpoint) const -> std::string
  {
    return send({HttpMethod::Get, endpoint}).body;
  }

  auto send(HttpRequest const& request) const -> HttpResponse override
  {
    httplib::Headers headers;
    for (auto const& [name, value] : request.headers)
    {
      headers.emplace(name, value);
    }

    httplib::Result result = [&]() -> httplib::Result {
      switch (request.method)
      {
      case HttpMethod::Get:
        return m_client->Get(request.path, headers);
      case HttpMethod::Post:
        return m_client->Post(request.path, headers, request.body, request.contentType);
      case HttpMethod::Put:
        return m_client->Put(request.path, headers, request.body, request.contentType);
      }
      throw std::runtime_error("Unsupported HTTP method");
    }();

    throwIfNotSuccessful(result, methodToString(request.method), request.path);

    HttpResponse response;
    // AXIVION Next Line CertC++-EXP34 : validity of the result variable is checked in throwIfNotSuccessful.
    response.statusCode = result->status;
    // AXIVION Next Line CertC++-EXP34 : validity of the result variable is checked in throwIfNotSuccessful.
    response.contentType = result->get_header_value("Content-Type");
    // AXIVION Next Line CertC++-EXP34 : validity of the result variable is checked in throwIfNotSuccessful.
    response.body = result->body;
    return response;
  }

  /**
   * @brief Provide raw access to the underlying httplib client.
   * 
   * This is useful for advanced configurations or operations not covered by this wrapper.
   * See the [httplib documentation](https://github.com/yhirose/cpp-httplib) options and details.
   */
  auto client() const -> ClientT&
  {
    return *m_client;
  }

  void enableErrorLogging()
  {
    m_client->set_error_logger([](httplib::Error const& err, httplib::Request const* req) -> void {
      std::string message = "Request ";
      if (req)
      {
        message += req->method + " " + req->path + " ";
      }
      message += "failed: " + httplib::to_string(err);
      LOG_ERROR("HttpClient") << message;
    });
  }

  void disableErrorLogging()
  {
    m_client->set_error_logger(nullptr);
  }

protected:
  std::unique_ptr<ClientT> m_client; // NOLINT(misc-non-private-member-variables-in-classes, cppcoreguidelines-non-private-member-variables-in-classes)

private:
  static auto methodToString(HttpMethod method) -> std::string
  {
    switch (method)
    {
    case HttpMethod::Get:
      return "GET";
    case HttpMethod::Post:
      return "POST";
    case HttpMethod::Put:
      return "PUT";
    }
    return "UNKNOWN";
  }

  static void throwIfNotSuccessful(httplib::Result const& result, std::string const& method, std::string const& endpoint)
  {
    if (!result)
    {
      switch (result.error())
      {
      case httplib::Error::SSLConnection:
        throw std::runtime_error("HTTP " + method + " " + endpoint + " failed due to SSL connection error: " + std::to_string(result.ssl_error()));
        break;
      case httplib::Error::SSLLoadingCerts:
        throw std::runtime_error("HTTP " + method + " " + endpoint + " failed due to SSL cert loading error: " + std::to_string(result.ssl_backend_error()));
        break;
      case httplib::Error::SSLServerVerification:
        throw std::runtime_error("HTTP " + method + " " + endpoint + " failed due to SSL verification error: " + std::to_string(result.ssl_backend_error()));
        break;
      case httplib::Error::SSLServerHostnameVerification:
        throw std::runtime_error(
          "HTTP " + method + " " + endpoint + " failed due to SSL hostname verification, X509 error: " + std::to_string(result.ssl_backend_error())
        );
        break;
      default:
        throw std::runtime_error("HTTP " + method + " " + endpoint + " failed: " + httplib::to_string(result.error()));
      }
    }
  }
};

} // namespace sick::httplib_client
