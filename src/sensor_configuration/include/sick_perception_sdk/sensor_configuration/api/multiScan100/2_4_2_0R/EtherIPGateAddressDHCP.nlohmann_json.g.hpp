/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPGateAddressDHCP.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherIPGateAddressDHCP.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherIPGateAddressDHCP::Get::Response const& obj)
{
  j = obj._EtherIPGateAddressDHCP;
}

inline void from_json(const nlohmann::json& j, EtherIPGateAddressDHCP::Get::Response& obj)
{
  j.get_to(obj._EtherIPGateAddressDHCP);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
