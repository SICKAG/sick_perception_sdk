/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackupResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/CreateParameterBackupResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

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


} // namespace sick::multiScan200::v1_1_0::api::rest
