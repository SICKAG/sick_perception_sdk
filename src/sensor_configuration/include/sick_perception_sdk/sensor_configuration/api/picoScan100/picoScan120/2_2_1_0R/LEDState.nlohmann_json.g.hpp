/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LEDState.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/LEDState.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LEDState::Get::Response::LEDStateItem const& obj)
{
  j = nlohmann::ordered_json{
      {"Color", obj._Color},
      {"Function", obj._Function},
      {"Id", obj._Id},
  };
}

inline void from_json(const nlohmann::json& j, LEDState::Get::Response::LEDStateItem& obj)
{
  j.at("Color").get_to(obj._Color);
  j.at("Function").get_to(obj._Function);
  j.at("Id").get_to(obj._Id);
}

inline void to_json(nlohmann::ordered_json& j, LEDState::Get::Response const& obj)
{
  j = obj._LEDState;
}

inline void from_json(const nlohmann::json& j, LEDState::Get::Response& obj)
{
  j.get_to(obj._LEDState);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
