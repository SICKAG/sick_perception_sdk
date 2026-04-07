/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableColaScan.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableColaScan.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EnableColaScan::Get::Response const& obj)
{
  j = obj._EnableColaScan;
}

inline void from_json(const nlohmann::json& j, EnableColaScan::Get::Response& obj)
{
  j.get_to(obj._EnableColaScan);
}


inline void to_json(nlohmann::ordered_json& j, EnableColaScan::Post::Request const& obj)
{
  j = obj._EnableColaScan;
}

inline void from_json(const nlohmann::json& j, EnableColaScan::Post::Request& obj)
{
  j.get_to(obj._EnableColaScan);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
