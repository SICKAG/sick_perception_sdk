/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPradialDistanceRangeFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/LFPradialDistanceRangeFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPradialDistanceRangeFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"ulDistMin", obj._ulDistMin.value()},
      {"ulDistMax", obj._ulDistMax.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPradialDistanceRangeFilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("ulDistMin").get_to(obj._ulDistMin);
  j.at("ulDistMax").get_to(obj._ulDistMax);
}


inline void to_json(nlohmann::ordered_json& j, LFPradialDistanceRangeFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"ulDistMin", obj._ulDistMin.value()},
      {"ulDistMax", obj._ulDistMax.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPradialDistanceRangeFilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("ulDistMin").get_to(obj._ulDistMin);
  j.at("ulDistMax").get_to(obj._ulDistMax);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
