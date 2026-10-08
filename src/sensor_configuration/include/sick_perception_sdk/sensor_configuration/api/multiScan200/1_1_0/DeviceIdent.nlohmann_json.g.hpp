/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceIdent.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/DeviceIdent.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, DeviceIdent::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Name", obj._Name},
      {"Version", obj._Version},
  };
}

inline void from_json(const nlohmann::json& j, DeviceIdent::Get::Response& obj)
{
  j.at("Name").get_to(obj._Name);
  j.at("Version").get_to(obj._Version);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
