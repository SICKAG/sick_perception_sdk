/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetWebserverEnabled.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/GetWebserverEnabled.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, GetWebserverEnabled::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"IsEnabled", obj._IsEnabled},
  };
}

inline void from_json(const nlohmann::json& j, GetWebserverEnabled::Post::Response& obj)
{
  j.at("IsEnabled").get_to(obj._IsEnabled);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
