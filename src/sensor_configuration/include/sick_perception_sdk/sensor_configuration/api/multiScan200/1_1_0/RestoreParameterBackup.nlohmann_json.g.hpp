/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RestoreParameterBackup.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/RestoreParameterBackup.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, RestoreParameterBackup::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Passphrase", obj._Passphrase},
      {"Filter", obj._Filter},
  };
}

inline void from_json(const nlohmann::json& j, RestoreParameterBackup::Post::Request& obj)
{
  j.at("Passphrase").get_to(obj._Passphrase);
  j.at("Filter").get_to(obj._Filter);
}


inline void to_json(nlohmann::ordered_json& j, RestoreParameterBackup::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Result", obj._Result},
  };
}

inline void from_json(const nlohmann::json& j, RestoreParameterBackup::Post::Response& obj)
{
  j.at("Result").get_to(obj._Result);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
