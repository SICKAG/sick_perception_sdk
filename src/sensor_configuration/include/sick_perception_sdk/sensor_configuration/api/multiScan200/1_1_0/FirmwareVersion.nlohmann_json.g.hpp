/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FirmwareVersion.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/FirmwareVersion.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, FirmwareVersion::Get::Response const& obj)
{
  j = obj._FirmwareVersion;
}

inline void from_json(const nlohmann::json& j, FirmwareVersion::Get::Response& obj)
{
  j.get_to(obj._FirmwareVersion);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
