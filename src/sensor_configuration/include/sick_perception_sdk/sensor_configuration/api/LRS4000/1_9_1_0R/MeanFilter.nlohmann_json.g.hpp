/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MeanFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/MeanFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, MeanFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiScanNumber", obj._uiScanNumber.value()},
      {"eFilterMethod", obj._eFilterMethod},
  };
}

inline void from_json(const nlohmann::json& j, MeanFilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiScanNumber").get_to(obj._uiScanNumber);
  j.at("eFilterMethod").get_to(obj._eFilterMethod);
}


inline void to_json(nlohmann::ordered_json& j, MeanFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiScanNumber", obj._uiScanNumber.value()},
      {"eFilterMethod", obj._eFilterMethod},
  };
}

inline void from_json(const nlohmann::json& j, MeanFilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiScanNumber").get_to(obj._uiScanNumber);
  j.at("eFilterMethod").get_to(obj._eFilterMethod);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
