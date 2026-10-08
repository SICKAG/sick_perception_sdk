/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file WriteEeprom.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/WriteEeprom.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_4::api::rest {

inline void to_json(nlohmann::ordered_json& j, WriteEeprom::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Success", obj._Success},
  };
}

inline void from_json(const nlohmann::json& j, WriteEeprom::Post::Response& obj)
{
  j.at("Success").get_to(obj._Success);
}


} // namespace sick::multiScan100::v2_4_4::api::rest
