/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataEthSettings.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/ScanDataEthSettings.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanDataEthSettings::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Protocol", obj._Protocol},
      {"IPAddress", obj._IPAddress},
      {"Port", obj._Port},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataEthSettings::Get::Response& obj)
{
  j.at("Protocol").get_to(obj._Protocol);
  j.at("IPAddress").get_to(obj._IPAddress);
  j.at("Port").get_to(obj._Port);
}


inline void to_json(nlohmann::ordered_json& j, ScanDataEthSettings::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Protocol", obj._Protocol},
      {"IPAddress", obj._IPAddress},
      {"Port", obj._Port},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataEthSettings::Post::Request& obj)
{
  j.at("Protocol").get_to(obj._Protocol);
  j.at("IPAddress").get_to(obj._IPAddress);
  j.at("Port").get_to(obj._Port);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
