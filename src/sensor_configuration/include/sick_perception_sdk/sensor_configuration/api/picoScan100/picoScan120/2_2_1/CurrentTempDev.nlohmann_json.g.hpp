/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CurrentTempDev.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/CurrentTempDev.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, CurrentTempDev::Get::Response const& obj)
{
  j = obj._CurrentTempDev;
}

inline void from_json(const nlohmann::json& j, CurrentTempDev::Get::Response& obj)
{
  j.get_to(obj._CurrentTempDev);
}


} // namespace sick::picoScan120::v2_2_1::api::rest
