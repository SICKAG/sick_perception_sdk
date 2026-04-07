/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableUserLevel.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EnableUserLevel.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, EnableUserLevel::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"userLevel", obj._userLevel},
      {"isEnabled", obj._isEnabled},
  };
}

inline void from_json(const nlohmann::json& j, EnableUserLevel::Post::Request& obj)
{
  j.at("userLevel").get_to(obj._userLevel);
  j.at("isEnabled").get_to(obj._isEnabled);
}


inline void to_json(nlohmann::ordered_json& j, EnableUserLevel::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"result", obj._result},
  };
}

inline void from_json(const nlohmann::json& j, EnableUserLevel::Post::Response& obj)
{
  j.at("result").get_to(obj._result);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
