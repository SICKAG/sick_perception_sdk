/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActualEncPosition2Enable.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/ActualEncPosition2Enable.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, ActualEncPosition2Enable::Get::Response const& obj)
{
  j = obj._ActualEncPosition2Enable;
}

inline void from_json(const nlohmann::json& j, ActualEncPosition2Enable::Get::Response& obj)
{
  j.get_to(obj._ActualEncPosition2Enable);
}


inline void to_json(nlohmann::ordered_json& j, ActualEncPosition2Enable::Post::Request const& obj)
{
  j = obj._ActualEncPosition2Enable;
}

inline void from_json(const nlohmann::json& j, ActualEncPosition2Enable::Post::Request& obj)
{
  j.get_to(obj._ActualEncPosition2Enable);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
