/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ParticleFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ParticleFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ParticleFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiThreshold", obj._uiThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, ParticleFilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiThreshold").get_to(obj._uiThreshold);
}


inline void to_json(nlohmann::ordered_json& j, ParticleFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"uiThreshold", obj._uiThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, ParticleFilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("uiThreshold").get_to(obj._uiThreshold);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
