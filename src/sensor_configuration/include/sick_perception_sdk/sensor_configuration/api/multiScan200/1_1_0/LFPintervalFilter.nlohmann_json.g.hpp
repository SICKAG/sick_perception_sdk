/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPintervalFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/LFPintervalFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

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


} // namespace sick::multiScan200::v1_1_0::api::rest
