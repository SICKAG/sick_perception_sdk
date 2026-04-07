/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationConfig.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/ContaminationConfig.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ContaminationConfig::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"eStrategy", obj._eStrategy},
      {"usiResponseTime", obj._usiResponseTime.value()},
      {"eThreshold", obj._eThreshold},
      {"eCover", obj._eCover},
      {"CustomSectors", obj._CustomSectors},
      {"bEnableWarning", obj._bEnableWarning},
      {"bEnableError", obj._bEnableError},
  };
}

inline void from_json(const nlohmann::json& j, ContaminationConfig::Get::Response& obj)
{
  j.at("eStrategy").get_to(obj._eStrategy);
  j.at("usiResponseTime").get_to(obj._usiResponseTime);
  j.at("eThreshold").get_to(obj._eThreshold);
  j.at("eCover").get_to(obj._eCover);
  j.at("CustomSectors").get_to(obj._CustomSectors);
  j.at("bEnableWarning").get_to(obj._bEnableWarning);
  j.at("bEnableError").get_to(obj._bEnableError);
}


inline void to_json(nlohmann::ordered_json& j, ContaminationConfig::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"eStrategy", obj._eStrategy},
      {"usiResponseTime", obj._usiResponseTime.value()},
      {"eThreshold", obj._eThreshold},
      {"eCover", obj._eCover},
      {"CustomSectors", obj._CustomSectors},
      {"bEnableWarning", obj._bEnableWarning},
      {"bEnableError", obj._bEnableError},
  };
}

inline void from_json(const nlohmann::json& j, ContaminationConfig::Post::Request& obj)
{
  j.at("eStrategy").get_to(obj._eStrategy);
  j.at("usiResponseTime").get_to(obj._usiResponseTime);
  j.at("eThreshold").get_to(obj._eThreshold);
  j.at("eCover").get_to(obj._eCover);
  j.at("CustomSectors").get_to(obj._CustomSectors);
  j.at("bEnableWarning").get_to(obj._bEnableWarning);
  j.at("bEnableError").get_to(obj._bEnableError);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
