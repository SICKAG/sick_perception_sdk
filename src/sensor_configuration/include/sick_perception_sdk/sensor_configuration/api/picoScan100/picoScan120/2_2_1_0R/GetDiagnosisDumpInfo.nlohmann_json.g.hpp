/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetDiagnosisDumpInfo.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/GetDiagnosisDumpInfo.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, GetDiagnosisDumpInfo::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"DiagDumpExists", obj._DiagDumpExists},
      {"DiagDumpTimestamp", obj._DiagDumpTimestamp},
  };
}

inline void from_json(const nlohmann::json& j, GetDiagnosisDumpInfo::Post::Response& obj)
{
  j.at("DiagDumpExists").get_to(obj._DiagDumpExists);
  j.at("DiagDumpTimestamp").get_to(obj._DiagDumpTimestamp);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
