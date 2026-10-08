/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherAuxIPPort.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/EtherAuxIPPort.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherAuxIPPort::Get::Response const& obj)
{
  j = obj._EtherAuxIPPort;
}

inline void from_json(const nlohmann::json& j, EtherAuxIPPort::Get::Response& obj)
{
  j.get_to(obj._EtherAuxIPPort);
}


inline void to_json(nlohmann::ordered_json& j, EtherAuxIPPort::Post::Request const& obj)
{
  j = obj._EtherAuxIPPort;
}

inline void from_json(const nlohmann::json& j, EtherAuxIPPort::Post::Request& obj)
{
  j.get_to(obj._EtherAuxIPPort);
}


} // namespace sick::picoScan120::v2_3_3::api::rest
