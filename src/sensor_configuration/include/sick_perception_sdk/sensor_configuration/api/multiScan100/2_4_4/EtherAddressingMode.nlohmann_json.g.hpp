/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherAddressingMode.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/EtherAddressingMode.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_4::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherAddressingMode::Get::Response const& obj)
{
  j = obj._EtherAddressingMode;
}

inline void from_json(const nlohmann::json& j, EtherAddressingMode::Get::Response& obj)
{
  j.get_to(obj._EtherAddressingMode);
}


inline void to_json(nlohmann::ordered_json& j, EtherAddressingMode::Post::Request const& obj)
{
  j = obj._EtherAddressingMode;
}

inline void from_json(const nlohmann::json& j, EtherAddressingMode::Post::Request& obj)
{
  j.get_to(obj._EtherAddressingMode);
}


} // namespace sick::multiScan100::v2_4_4::api::rest
