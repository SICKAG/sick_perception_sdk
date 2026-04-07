/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "TestHttpClient.hpp"

namespace sick::test {

auto TestHttpClient::get(std::string const& endpoint) const -> std::string
{
  requestedGetEndpoints.push_back(endpoint);
  auto response = getResponses.front();
  getResponses.pop_front();
  return response;
}

auto TestHttpClient::post(std::string const& endpoint, std::string const& payload) const -> std::string
{
  requestedPostEndpoints.push_back(endpoint);
  requestedPostPayloads.push_back(payload);
  auto response = postResponses.front();
  postResponses.pop_front();
  return response;
}

} // namespace sick::test
