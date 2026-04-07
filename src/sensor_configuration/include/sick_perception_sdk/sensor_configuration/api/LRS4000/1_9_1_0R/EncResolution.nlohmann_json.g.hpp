/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncResolution.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncResolution.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EncResolution::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"EncResolution", obj._EncResolution},
  };
}

inline void from_json(const nlohmann::json& j, EncResolution::Post::Request& obj)
{
  j.at("EncResolution").get_to(obj._EncResolution);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
