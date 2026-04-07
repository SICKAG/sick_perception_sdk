/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPMaskDHCP.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherIPMaskDHCP.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherIPMaskDHCP::Get::Response const& obj)
{
  j = obj._EtherIPMaskDHCP;
}

inline void from_json(const nlohmann::json& j, EtherIPMaskDHCP::Get::Response& obj)
{
  j.get_to(obj._EtherIPMaskDHCP);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
