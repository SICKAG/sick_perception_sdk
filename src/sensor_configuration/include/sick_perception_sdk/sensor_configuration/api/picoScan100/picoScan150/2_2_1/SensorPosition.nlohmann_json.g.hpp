/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensorPosition.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/SensorPosition.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, SensorPosition::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x.value()},
      {"y", obj._y.value()},
      {"z", obj._z.value()},
      {"yaw", obj._yaw.value()},
      {"pitch", obj._pitch.value()},
      {"roll", obj._roll.value()},
  };
}

inline void from_json(const nlohmann::json& j, SensorPosition::Get::Response& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
  j.at("yaw").get_to(obj._yaw);
  j.at("pitch").get_to(obj._pitch);
  j.at("roll").get_to(obj._roll);
}


inline void to_json(nlohmann::ordered_json& j, SensorPosition::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x.value()},
      {"y", obj._y.value()},
      {"z", obj._z.value()},
      {"yaw", obj._yaw.value()},
      {"pitch", obj._pitch.value()},
      {"roll", obj._roll.value()},
  };
}

inline void from_json(const nlohmann::json& j, SensorPosition::Post::Request& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
  j.at("yaw").get_to(obj._yaw);
  j.at("pitch").get_to(obj._pitch);
  j.at("roll").get_to(obj._roll);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
