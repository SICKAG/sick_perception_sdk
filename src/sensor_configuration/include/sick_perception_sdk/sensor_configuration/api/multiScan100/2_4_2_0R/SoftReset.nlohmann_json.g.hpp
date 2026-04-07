/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SoftReset.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/SoftReset.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, SoftReset::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"ProcessorNbr", obj._ProcessorNbr},
  };
}

inline void from_json(const nlohmann::json& j, SoftReset::Post::Request& obj)
{
  j.at("ProcessorNbr").get_to(obj._ProcessorNbr);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
