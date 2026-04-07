/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPradialDistanceRangeFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPradialDistanceRangeFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

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


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
