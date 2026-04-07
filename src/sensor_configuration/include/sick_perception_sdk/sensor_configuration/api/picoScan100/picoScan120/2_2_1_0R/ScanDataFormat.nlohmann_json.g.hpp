/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataFormat.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/ScanDataFormat.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanDataFormat::Get::Response const& obj)
{
  j = obj._ScanDataFormat;
}

inline void from_json(const nlohmann::json& j, ScanDataFormat::Get::Response& obj)
{
  j.get_to(obj._ScanDataFormat);
}


inline void to_json(nlohmann::ordered_json& j, ScanDataFormat::Post::Request const& obj)
{
  j = obj._ScanDataFormat;
}

inline void from_json(const nlohmann::json& j, ScanDataFormat::Post::Request& obj)
{
  j.get_to(obj._ScanDataFormat);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
