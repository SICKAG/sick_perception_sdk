/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataPreformatting.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/ScanDataPreformatting.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_4::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanDataPreformatting::Get::Response const& obj)
{
  j = obj._ScanDataPreformatting;
}

inline void from_json(const nlohmann::json& j, ScanDataPreformatting::Get::Response& obj)
{
  j.get_to(obj._ScanDataPreformatting);
}


inline void to_json(nlohmann::ordered_json& j, ScanDataPreformatting::Post::Request const& obj)
{
  j = obj._ScanDataPreformatting;
}

inline void from_json(const nlohmann::json& j, ScanDataPreformatting::Post::Request& obj)
{
  j.get_to(obj._ScanDataPreformatting);
}


} // namespace sick::multiScan100::v2_4_4::api::rest
