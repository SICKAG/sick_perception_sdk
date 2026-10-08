/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationActiveSectors.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/ContaminationActiveSectors.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, ContaminationActiveSectors::Get::Response const& obj)
{
  j = obj._ContaminationActiveSectors;
}

inline void from_json(const nlohmann::json& j, ContaminationActiveSectors::Get::Response& obj)
{
  j.get_to(obj._ContaminationActiveSectors);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
