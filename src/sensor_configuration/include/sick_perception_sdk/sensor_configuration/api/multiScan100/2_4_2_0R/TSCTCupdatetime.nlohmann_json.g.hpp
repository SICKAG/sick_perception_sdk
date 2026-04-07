/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCupdatetime.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCTCupdatetime.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, TSCTCupdatetime::Get::Response const& obj)
{
  j = obj._TSCTCupdatetime.value();
}

inline void from_json(const nlohmann::json& j, TSCTCupdatetime::Get::Response& obj)
{
  j.get_to(obj._TSCTCupdatetime);
}


inline void to_json(nlohmann::ordered_json& j, TSCTCupdatetime::Post::Request const& obj)
{
  j = obj._TSCTCupdatetime.value();
}

inline void from_json(const nlohmann::json& j, TSCTCupdatetime::Post::Request& obj)
{
  j.get_to(obj._TSCTCupdatetime);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
