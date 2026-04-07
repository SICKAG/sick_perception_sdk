/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetScanConfigList.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetScanConfigList.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetScanConfigList::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"ScanConfigList", obj._ScanConfigList},
  };
}

inline void from_json(const nlohmann::json& j, SetScanConfigList::Post::Request& obj)
{
  j.at("ScanConfigList").get_to(obj._ScanConfigList);
}


inline void to_json(nlohmann::ordered_json& j, SetScanConfigList::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"eScanConfigError", obj._eScanConfigError},
  };
}

inline void from_json(const nlohmann::json& j, SetScanConfigList::Post::Response& obj)
{
  j.at("eScanConfigError").get_to(obj._eScanConfigError);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
