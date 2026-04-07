/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InertialMeasurementUnit.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/InertialMeasurementUnit.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

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


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
