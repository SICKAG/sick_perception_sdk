/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetOutput.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/SetOutput.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetOutput::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"Output", obj._Output},
      {"Value", obj._Value},
  };
}

inline void from_json(const nlohmann::json& j, SetOutput::Post::Request& obj)
{
  j.at("Output").get_to(obj._Output);
  j.at("Value").get_to(obj._Value);
}


inline void to_json(nlohmann::ordered_json& j, SetOutput::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Success", obj._Success},
  };
}

inline void from_json(const nlohmann::json& j, SetOutput::Post::Response& obj)
{
  j.at("Success").get_to(obj._Success);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
