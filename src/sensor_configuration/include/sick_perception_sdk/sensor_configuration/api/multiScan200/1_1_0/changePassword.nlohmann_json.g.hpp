/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file changePassword.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/changePassword.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, changePassword::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"encryptedMessage", obj._encryptedMessage},
      {"userLevel", obj._userLevel},
  };
}

inline void from_json(const nlohmann::json& j, changePassword::Post::Request& obj)
{
  j.at("encryptedMessage").get_to(obj._encryptedMessage);
  j.at("userLevel").get_to(obj._userLevel);
}


inline void to_json(nlohmann::ordered_json& j, changePassword::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"result", obj._result},
  };
}

inline void from_json(const nlohmann::json& j, changePassword::Post::Response& obj)
{
  j.at("result").get_to(obj._result);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
