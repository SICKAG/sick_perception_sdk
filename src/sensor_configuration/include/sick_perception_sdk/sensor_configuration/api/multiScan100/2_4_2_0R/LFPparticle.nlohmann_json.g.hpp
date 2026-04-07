/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPparticle.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPparticle.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

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


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
