/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPintervalFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/LFPintervalFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPintervalFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiReductionFactor", obj._uiReductionFactor.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPintervalFilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiReductionFactor").get_to(obj._uiReductionFactor);
}


inline void to_json(nlohmann::ordered_json& j, LFPintervalFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiReductionFactor", obj._uiReductionFactor.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPintervalFilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiReductionFactor").get_to(obj._uiReductionFactor);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
