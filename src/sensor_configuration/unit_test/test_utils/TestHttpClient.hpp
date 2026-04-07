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

class TestHttpClient : public sick::IHttpClient
{
public:
  TestHttpClient()           = default;
  ~TestHttpClient() override = default;

  auto get(std::string const& endpoint) const -> std::string override;
  auto post(std::string const& endpoint, std::string const& payload) const -> std::string override;

  mutable std::vector<std::string> requestedGetEndpoints;
  mutable std::deque<std::string> getResponses;
  mutable std::vector<std::string> requestedPostEndpoints;
  mutable std::vector<std::string> requestedPostPayloads;
  mutable std::deque<std::string> postResponses;
};

} // namespace sick::test
