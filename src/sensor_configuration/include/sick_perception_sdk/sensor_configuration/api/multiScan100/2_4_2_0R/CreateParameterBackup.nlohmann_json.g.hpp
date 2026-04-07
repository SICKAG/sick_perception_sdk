/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackup.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/CreateParameterBackup.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, CreateParameterBackup::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Passphrase", obj._Passphrase},
  };
}

inline void from_json(const nlohmann::json& j, CreateParameterBackup::Post::Request& obj)
{
  j.at("Passphrase").get_to(obj._Passphrase);
}


inline void to_json(nlohmann::ordered_json& j, CreateParameterBackup::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Result", obj._Result},
  };
}

inline void from_json(const nlohmann::json& j, CreateParameterBackup::Post::Response& obj)
{
  j.at("Result").get_to(obj._Result);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
