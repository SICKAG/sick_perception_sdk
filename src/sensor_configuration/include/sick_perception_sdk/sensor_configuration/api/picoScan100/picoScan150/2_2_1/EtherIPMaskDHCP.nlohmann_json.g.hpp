/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPMaskDHCP.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/EtherIPMaskDHCP.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherIPMaskDHCP::Get::Response const& obj)
{
  j = obj._EtherIPMaskDHCP;
}

inline void from_json(const nlohmann::json& j, EtherIPMaskDHCP::Get::Response& obj)
{
  j.get_to(obj._EtherIPMaskDHCP);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
