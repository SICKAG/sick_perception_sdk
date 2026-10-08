/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MergeSaving.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/MergeSaving.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, MergeSaving::Get::Response const& obj)
{
  j = obj._MergeSaving;
}

inline void from_json(const nlohmann::json& j, MergeSaving::Get::Response& obj)
{
  j.get_to(obj._MergeSaving);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
