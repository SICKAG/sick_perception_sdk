/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderRotation.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/EncoderRotation.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, EncoderRotation::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"yaw", obj._yaw},
      {"pitch", obj._pitch},
      {"roll", obj._roll},
  };
}

inline void from_json(const nlohmann::json& j, EncoderRotation::Get::Response& obj)
{
  j.at("yaw").get_to(obj._yaw);
  j.at("pitch").get_to(obj._pitch);
  j.at("roll").get_to(obj._roll);
}


inline void to_json(nlohmann::ordered_json& j, EncoderRotation::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"yaw", obj._yaw},
      {"pitch", obj._pitch},
      {"roll", obj._roll},
  };
}

inline void from_json(const nlohmann::json& j, EncoderRotation::Post::Request& obj)
{
  j.at("yaw").get_to(obj._yaw);
  j.at("pitch").get_to(obj._pitch);
  j.at("roll").get_to(obj._roll);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
