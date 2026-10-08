/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetPassword.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/SetPassword.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetPassword::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"siUserLevel", obj._siUserLevel},
      {"udiNewPassword", obj._udiNewPassword},
  };
}

inline void from_json(const nlohmann::json& j, SetPassword::Post::Request& obj)
{
  j.at("siUserLevel").get_to(obj._siUserLevel);
  j.at("udiNewPassword").get_to(obj._udiNewPassword);
}


inline void to_json(nlohmann::ordered_json& j, SetPassword::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bSuccess", obj._bSuccess},
  };
}

inline void from_json(const nlohmann::json& j, SetPassword::Post::Response& obj)
{
  j.at("bSuccess").get_to(obj._bSuccess);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
