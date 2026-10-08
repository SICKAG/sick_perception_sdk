/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file enableCloningPlug.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/enableCloningPlug.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, enableCloningPlug::Get::Response const& obj)
{
  j = obj._enableCloningPlug;
}

inline void from_json(const nlohmann::json& j, enableCloningPlug::Get::Response& obj)
{
  j.get_to(obj._enableCloningPlug);
}


inline void to_json(nlohmann::ordered_json& j, enableCloningPlug::Post::Request const& obj)
{
  j = obj._enableCloningPlug;
}

inline void from_json(const nlohmann::json& j, enableCloningPlug::Post::Request& obj)
{
  j.get_to(obj._enableCloningPlug);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
