/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/ContaminationResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, ContaminationResult::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bWarningActive", obj._bWarningActive},
      {"bErrorActive", obj._bErrorActive},
  };
}

inline void from_json(const nlohmann::json& j, ContaminationResult::Get::Response& obj)
{
  j.at("bWarningActive").get_to(obj._bWarningActive);
  j.at("bErrorActive").get_to(obj._bErrorActive);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
