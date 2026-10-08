/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableLegacyUserLevel.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EnableLegacyUserLevel.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, EnableLegacyUserLevel::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"userLevel", obj._userLevel.value()},
      {"isEnabled", obj._isEnabled},
  };
}

inline void from_json(const nlohmann::json& j, EnableLegacyUserLevel::Post::Request& obj)
{
  j.at("userLevel").get_to(obj._userLevel);
  j.at("isEnabled").get_to(obj._isEnabled);
}


inline void to_json(nlohmann::ordered_json& j, EnableLegacyUserLevel::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"result", obj._result},
  };
}

inline void from_json(const nlohmann::json& j, EnableLegacyUserLevel::Post::Response& obj)
{
  j.at("result").get_to(obj._result);
}


} // namespace sick::picoScan120::v2_2_1::api::rest
