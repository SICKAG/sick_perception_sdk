/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherCoLaScanMode.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/EtherCoLaScanMode.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EtherCoLaScanMode::Get::Response const& obj)
{
  j = obj._EtherCoLaScanMode;
}

inline void from_json(const nlohmann::json& j, EtherCoLaScanMode::Get::Response& obj)
{
  j.get_to(obj._EtherCoLaScanMode);
}


inline void to_json(nlohmann::ordered_json& j, EtherCoLaScanMode::Post::Request const& obj)
{
  j = obj._EtherCoLaScanMode;
}

inline void from_json(const nlohmann::json& j, EtherCoLaScanMode::Post::Request& obj)
{
  j.get_to(obj._EtherCoLaScanMode);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
