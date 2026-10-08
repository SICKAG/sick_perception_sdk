/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file particleFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/particleFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, particleFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"minNumberOfNeighbors", obj._minNumberOfNeighbors},
      {"distanceThreshold", obj._distanceThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, particleFilter::Get::Response& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("minNumberOfNeighbors").get_to(obj._minNumberOfNeighbors);
  j.at("distanceThreshold").get_to(obj._distanceThreshold);
}


inline void to_json(nlohmann::ordered_json& j, particleFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"minNumberOfNeighbors", obj._minNumberOfNeighbors},
      {"distanceThreshold", obj._distanceThreshold.value()},
  };
}

inline void from_json(const nlohmann::json& j, particleFilter::Post::Request& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("minNumberOfNeighbors").get_to(obj._minNumberOfNeighbors);
  j.at("distanceThreshold").get_to(obj._distanceThreshold);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
