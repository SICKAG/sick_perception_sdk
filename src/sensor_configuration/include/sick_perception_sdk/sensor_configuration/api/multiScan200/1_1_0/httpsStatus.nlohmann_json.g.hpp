/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file httpsStatus.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/httpsStatus.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, httpsStatus::Get::Response::errorCode const& obj)
{
  j = nlohmann::ordered_json{
      {"error", obj._error},
  };
}

inline void from_json(const nlohmann::json& j, httpsStatus::Get::Response::errorCode& obj)
{
  j.at("error").get_to(obj._error);
}

inline void to_json(nlohmann::ordered_json& j, httpsStatus::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"enabled", obj._enabled},
      {"errorCode", obj._errorCode},
  };
}

inline void from_json(const nlohmann::json& j, httpsStatus::Get::Response& obj)
{
  j.at("enabled").get_to(obj._enabled);
  j.at("errorCode").get_to(obj._errorCode);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
