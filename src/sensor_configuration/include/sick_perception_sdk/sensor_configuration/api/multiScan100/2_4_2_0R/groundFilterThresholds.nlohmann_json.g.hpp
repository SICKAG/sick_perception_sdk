/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file groundFilterThresholds.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/groundFilterThresholds.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, groundFilterThresholds::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"minimumDistance", obj._minimumDistance.value()},
      {"maximumDistance", obj._maximumDistance.value()},
  };
}

inline void from_json(const nlohmann::json& j, groundFilterThresholds::Get::Response& obj)
{
  j.at("minimumDistance").get_to(obj._minimumDistance);
  j.at("maximumDistance").get_to(obj._maximumDistance);
}


inline void to_json(nlohmann::ordered_json& j, groundFilterThresholds::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"minimumDistance", obj._minimumDistance.value()},
      {"maximumDistance", obj._maximumDistance.value()},
  };
}

inline void from_json(const nlohmann::json& j, groundFilterThresholds::Post::Request& obj)
{
  j.at("minimumDistance").get_to(obj._minimumDistance);
  j.at("maximumDistance").get_to(obj._maximumDistance);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
