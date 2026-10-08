/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InertialMeasurementUnit.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/InertialMeasurementUnit.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, InertialMeasurementUnit::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Acceleration", obj._Acceleration},
      {"AngularVelocity", obj._AngularVelocity},
      {"Orientation", obj._Orientation},
      {"TimeStamp", obj._TimeStamp},
  };
}

inline void from_json(const nlohmann::json& j, InertialMeasurementUnit::Get::Response& obj)
{
  j.at("Acceleration").get_to(obj._Acceleration);
  j.at("AngularVelocity").get_to(obj._AngularVelocity);
  j.at("Orientation").get_to(obj._Orientation);
  j.at("TimeStamp").get_to(obj._TimeStamp);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
