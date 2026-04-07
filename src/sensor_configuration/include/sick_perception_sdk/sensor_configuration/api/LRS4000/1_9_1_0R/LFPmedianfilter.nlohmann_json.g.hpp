/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPmedianfilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPmedianfilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPmedianfilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiMedianWidth", obj._uiMedianWidth.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPmedianfilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiMedianWidth").get_to(obj._uiMedianWidth);
}


inline void to_json(nlohmann::ordered_json& j, LFPmedianfilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiMedianWidth", obj._uiMedianWidth.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPmedianfilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiMedianWidth").get_to(obj._uiMedianWidth);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
