/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <string>
#include <utility>
#include <vector>

namespace sick {

auto sessionHeaders(std::string const& token) -> std::vector<std::pair<std::string, std::string>>;

void throwIfNotOk(HttpResponse const& response, std::string const& context);

} // namespace sick
