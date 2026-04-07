/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ContaminationResult::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"warningActive", obj._warningActive},
      {"errorActive", obj._errorActive},
  };
}

inline void from_json(const nlohmann::json& j, ContaminationResult::Get::Response& obj)
{
  j.at("warningActive").get_to(obj._warningActive);
  j.at("errorActive").get_to(obj._errorActive);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
