/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "HttpHelpers.hpp"

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace sick {

auto sessionHeaders(std::string const& token) -> std::vector<std::pair<std::string, std::string>>
{
  return {{"X-Session-Token", token}};
}

void throwIfNotOk(HttpResponse const& response, std::string const& context)
{
  constexpr int kHttpOk = 200;
  if (response.statusCode != kHttpOk)
  {
    throw std::runtime_error(context + " failed with HTTP status " + std::to_string(response.statusCode));
  }
}

} // namespace sick
