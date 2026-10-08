/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "TestHttpClient.hpp"

#include <stdexcept>
#include <utility>

namespace sick::test {

auto TestHttpClient::send(HttpRequest const& request) const -> HttpResponse
{
  requests.push_back(request);
  if (responses.empty())
  {
    throw std::runtime_error("TestHttpClient: no queued response for " + request.path);
  }
  auto response = responses.front();
  responses.pop_front();
  return response;
}

void TestHttpClient::queueJsonResponse(std::string body) const
{
  queueResponse(200, std::move(body), "application/json");
}

void TestHttpClient::queueResponse(int statusCode, std::string body, std::string contentType) const
{
  HttpResponse response;
  response.statusCode  = statusCode;
  response.contentType = std::move(contentType);
  response.body        = std::move(body);
  responses.push_back(std::move(response));
}

} // namespace sick::test
