/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCRole.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCRole.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_10_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, TSCRole::Get::Response const& obj)
{
  j = obj._TSCRole;
}

inline void from_json(const nlohmann::json& j, TSCRole::Get::Response& obj)
{
  j.get_to(obj._TSCRole);
}


inline void to_json(nlohmann::ordered_json& j, TSCRole::Post::Request const& obj)
{
  j = obj._TSCRole;
}

inline void from_json(const nlohmann::json& j, TSCRole::Post::Request& obj)
{
  j.get_to(obj._TSCRole);
}


} // namespace sick::LRS4000::v1_10_0::api::rest
