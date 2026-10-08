/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackupResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/CreateParameterBackupResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, CreateParameterBackupResult::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Status", obj._Status},
      {"Result", obj._Result},
  };
}

inline void from_json(const nlohmann::json& j, CreateParameterBackupResult::Get::Response& obj)
{
  j.at("Status").get_to(obj._Status);
  j.at("Result").get_to(obj._Result);
}


} // namespace sick::picoScan120::v2_3_3::api::rest
