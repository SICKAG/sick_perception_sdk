/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InertialMeasurementUnit.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/InertialMeasurementUnit.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, InertialMeasurementUnit::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Acceleration", obj._Acceleration},
      {"AngularVelocity", obj._AngularVelocity},
      {"MagneticField", obj._MagneticField},
      {"Orientation", obj._Orientation},
      {"TimeStamp", obj._TimeStamp},
  };
}

inline void from_json(const nlohmann::json& j, InertialMeasurementUnit::Get::Response& obj)
{
  j.at("Acceleration").get_to(obj._Acceleration);
  j.at("AngularVelocity").get_to(obj._AngularVelocity);
  j.at("MagneticField").get_to(obj._MagneticField);
  j.at("Orientation").get_to(obj._Orientation);
  j.at("TimeStamp").get_to(obj._TimeStamp);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
