/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataConfig.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/ScanDataConfig.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanDataConfig::Get::Response::RemDataConfig const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"reserved1", obj._reserved1},
      {"reserved2", obj._reserved2},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataConfig::Get::Response::RemDataConfig& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("reserved1").get_to(obj._reserved1);
  j.at("reserved2").get_to(obj._reserved2);
}

inline void to_json(nlohmann::ordered_json& j, ScanDataConfig::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"reserved", obj._reserved},
      {"RemDataConfig", obj._RemDataConfig},
      {"EnableEncoderBlock", obj._EnableEncoderBlock},
      {"reserved1", obj._reserved1},
      {"bEnableDeviceName", obj._bEnableDeviceName},
      {"reserved2", obj._reserved2},
      {"bEnableTimeBlock", obj._bEnableTimeBlock},
      {"reserved3", obj._reserved3},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataConfig::Get::Response& obj)
{
  j.at("reserved").get_to(obj._reserved);
  j.at("RemDataConfig").get_to(obj._RemDataConfig);
  j.at("EnableEncoderBlock").get_to(obj._EnableEncoderBlock);
  j.at("reserved1").get_to(obj._reserved1);
  j.at("bEnableDeviceName").get_to(obj._bEnableDeviceName);
  j.at("reserved2").get_to(obj._reserved2);
  j.at("bEnableTimeBlock").get_to(obj._bEnableTimeBlock);
  j.at("reserved3").get_to(obj._reserved3);
}


inline void to_json(nlohmann::ordered_json& j, ScanDataConfig::Post::Request::RemDataConfig const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"reserved1", obj._reserved1},
      {"reserved2", obj._reserved2},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataConfig::Post::Request::RemDataConfig& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("reserved1").get_to(obj._reserved1);
  j.at("reserved2").get_to(obj._reserved2);
}

inline void to_json(nlohmann::ordered_json& j, ScanDataConfig::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"reserved", obj._reserved},
      {"RemDataConfig", obj._RemDataConfig},
      {"EnableEncoderBlock", obj._EnableEncoderBlock},
      {"reserved1", obj._reserved1},
      {"bEnableDeviceName", obj._bEnableDeviceName},
      {"reserved2", obj._reserved2},
      {"bEnableTimeBlock", obj._bEnableTimeBlock},
      {"reserved3", obj._reserved3},
  };
}

inline void from_json(const nlohmann::json& j, ScanDataConfig::Post::Request& obj)
{
  j.at("reserved").get_to(obj._reserved);
  j.at("RemDataConfig").get_to(obj._RemDataConfig);
  j.at("EnableEncoderBlock").get_to(obj._EnableEncoderBlock);
  j.at("reserved1").get_to(obj._reserved1);
  j.at("bEnableDeviceName").get_to(obj._bEnableDeviceName);
  j.at("reserved2").get_to(obj._reserved2);
  j.at("bEnableTimeBlock").get_to(obj._bEnableTimeBlock);
  j.at("reserved3").get_to(obj._reserved3);
}


} // namespace sick::picoScan120::v2_3_3::api::rest
