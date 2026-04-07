/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ImuDataEthSettings.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ImuDataEthSettings.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ImuDataEthSettings::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Protocol", obj._Protocol},
      {"IPAddress", obj._IPAddress},
      {"Port", obj._Port},
  };
}

inline void from_json(const nlohmann::json& j, ImuDataEthSettings::Get::Response& obj)
{
  j.at("Protocol").get_to(obj._Protocol);
  j.at("IPAddress").get_to(obj._IPAddress);
  j.at("Port").get_to(obj._Port);
}


inline void to_json(nlohmann::ordered_json& j, ImuDataEthSettings::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Protocol", obj._Protocol},
      {"IPAddress", obj._IPAddress},
      {"Port", obj._Port},
  };
}

inline void from_json(const nlohmann::json& j, ImuDataEthSettings::Post::Request& obj)
{
  j.at("Protocol").get_to(obj._Protocol);
  j.at("IPAddress").get_to(obj._IPAddress);
  j.at("Port").get_to(obj._Port);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
