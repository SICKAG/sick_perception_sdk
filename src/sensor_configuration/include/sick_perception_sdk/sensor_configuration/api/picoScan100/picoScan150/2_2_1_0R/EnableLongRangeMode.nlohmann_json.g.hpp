/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableLongRangeMode.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/EnableLongRangeMode.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EnableLongRangeMode::Get::Response const& obj)
{
  j = obj._EnableLongRangeMode;
}

inline void from_json(const nlohmann::json& j, EnableLongRangeMode::Get::Response& obj)
{
  j.get_to(obj._EnableLongRangeMode);
}


inline void to_json(nlohmann::ordered_json& j, EnableLongRangeMode::Post::Request const& obj)
{
  j = obj._EnableLongRangeMode;
}

inline void from_json(const nlohmann::json& j, EnableLongRangeMode::Post::Request& obj)
{
  j.get_to(obj._EnableLongRangeMode);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
