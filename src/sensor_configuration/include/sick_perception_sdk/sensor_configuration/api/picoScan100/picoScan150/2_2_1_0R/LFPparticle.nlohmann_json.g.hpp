/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPparticle.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/LFPparticle.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPparticle::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiThreshold", obj._uiThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPparticle::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiThreshold").get_to(obj._uiThreshold);
}


inline void to_json(nlohmann::ordered_json& j, LFPparticle::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiThreshold", obj._uiThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPparticle::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiThreshold").get_to(obj._uiThreshold);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
