/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file AutoStartMeasure.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/AutoStartMeasure.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, AutoStartMeasure::Get::Response const& obj)
{
  j = obj._AutoStartMeasure;
}

inline void from_json(const nlohmann::json& j, AutoStartMeasure::Get::Response& obj)
{
  j.get_to(obj._AutoStartMeasure);
}


inline void to_json(nlohmann::ordered_json& j, AutoStartMeasure::Post::Request const& obj)
{
  j = obj._AutoStartMeasure;
}

inline void from_json(const nlohmann::json& j, AutoStartMeasure::Post::Request& obj)
{
  j.get_to(obj._AutoStartMeasure);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
