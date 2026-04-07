/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FREchoFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/FREchoFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, FREchoFilter::Get::Response const& obj)
{
  j = obj._FREchoFilter;
}

inline void from_json(const nlohmann::json& j, FREchoFilter::Get::Response& obj)
{
  j.get_to(obj._FREchoFilter);
}


inline void to_json(nlohmann::ordered_json& j, FREchoFilter::Post::Request const& obj)
{
  j = obj._FREchoFilter;
}

inline void from_json(const nlohmann::json& j, FREchoFilter::Post::Request& obj)
{
  j.get_to(obj._FREchoFilter);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
