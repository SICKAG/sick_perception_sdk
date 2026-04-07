/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmConfiguration.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/temperatureAlarmConfiguration.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, temperatureAlarmConfiguration::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"upperThreshold", obj._upperThreshold},
      {"lowerThreshold", obj._lowerThreshold},
  };
}

inline void from_json(const nlohmann::json& j, temperatureAlarmConfiguration::Get::Response& obj)
{
  j.at("upperThreshold").get_to(obj._upperThreshold);
  j.at("lowerThreshold").get_to(obj._lowerThreshold);
}


inline void to_json(nlohmann::ordered_json& j, temperatureAlarmConfiguration::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"upperThreshold", obj._upperThreshold},
      {"lowerThreshold", obj._lowerThreshold},
  };
}

inline void from_json(const nlohmann::json& j, temperatureAlarmConfiguration::Post::Request& obj)
{
  j.at("upperThreshold").get_to(obj._upperThreshold);
  j.at("lowerThreshold").get_to(obj._lowerThreshold);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
