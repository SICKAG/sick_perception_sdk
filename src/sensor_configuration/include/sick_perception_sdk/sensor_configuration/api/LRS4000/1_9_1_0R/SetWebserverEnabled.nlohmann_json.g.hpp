/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetWebserverEnabled.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetWebserverEnabled.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetWebserverEnabled::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Enable", obj._Enable},
  };
}

inline void from_json(const nlohmann::json& j, SetWebserverEnabled::Post::Request& obj)
{
  j.at("Enable").get_to(obj._Enable);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
