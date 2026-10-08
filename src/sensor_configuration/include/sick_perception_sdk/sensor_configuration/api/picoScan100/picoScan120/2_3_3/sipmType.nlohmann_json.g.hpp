/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file sipmType.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/sipmType.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, sipmType::Get::Response const& obj)
{
  j = obj._sipmType;
}

inline void from_json(const nlohmann::json& j, sipmType::Get::Response& obj)
{
  j.get_to(obj._sipmType);
}


} // namespace sick::picoScan120::v2_3_3::api::rest
