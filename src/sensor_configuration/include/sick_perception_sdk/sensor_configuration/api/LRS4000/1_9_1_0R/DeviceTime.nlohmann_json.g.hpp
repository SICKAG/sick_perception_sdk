/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceTime.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceTime.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, DeviceTime::Get::Response const& obj)
{
  j = obj._DeviceTime;
}

inline void from_json(const nlohmann::json& j, DeviceTime::Get::Response& obj)
{
  j.get_to(obj._DeviceTime);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
