/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file enableHighPrecisionMode.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/enableHighPrecisionMode.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, enableHighPrecisionMode::Get::Response const& obj)
{
  j = obj._enableHighPrecisionMode;
}

inline void from_json(const nlohmann::json& j, enableHighPrecisionMode::Get::Response& obj)
{
  j.get_to(obj._enableHighPrecisionMode);
}


inline void to_json(nlohmann::ordered_json& j, enableHighPrecisionMode::Post::Request const& obj)
{
  j = obj._enableHighPrecisionMode;
}

inline void from_json(const nlohmann::json& j, enableHighPrecisionMode::Post::Request& obj)
{
  j.get_to(obj._enableHighPrecisionMode);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
