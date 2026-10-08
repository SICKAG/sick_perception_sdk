/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderTranslation.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/EncoderTranslation.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, EncoderTranslation::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x},
      {"y", obj._y},
      {"z", obj._z},
  };
}

inline void from_json(const nlohmann::json& j, EncoderTranslation::Get::Response& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
}


inline void to_json(nlohmann::ordered_json& j, EncoderTranslation::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x},
      {"y", obj._y},
      {"z", obj._z},
  };
}

inline void from_json(const nlohmann::json& j, EncoderTranslation::Post::Request& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
