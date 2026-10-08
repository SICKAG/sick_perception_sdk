/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanMergeTrigger.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/ScanMergeTrigger.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanMergeTrigger::Get::Response const& obj)
{
  j = obj._ScanMergeTrigger;
}

inline void from_json(const nlohmann::json& j, ScanMergeTrigger::Get::Response& obj)
{
  j.get_to(obj._ScanMergeTrigger);
}


inline void to_json(nlohmann::ordered_json& j, ScanMergeTrigger::Post::Request const& obj)
{
  j = obj._ScanMergeTrigger;
}

inline void from_json(const nlohmann::json& j, ScanMergeTrigger::Post::Request& obj)
{
  j.get_to(obj._ScanMergeTrigger);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
