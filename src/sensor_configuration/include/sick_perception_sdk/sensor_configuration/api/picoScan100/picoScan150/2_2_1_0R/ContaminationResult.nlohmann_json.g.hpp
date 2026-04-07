/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/ContaminationResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

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


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
