/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFTchecksum.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/LFTchecksum.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFTchecksum::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"MD5SumOK", obj._MD5SumOK},
      {"MD5LinuxRoot", obj._MD5LinuxRoot},
      {"MD5App", obj._MD5App},
      {"MD5Calibration", obj._MD5Calibration},
      {"MD5Parameters", obj._MD5Parameters},
  };
}

inline void from_json(const nlohmann::json& j, LFTchecksum::Get::Response& obj)
{
  j.at("MD5SumOK").get_to(obj._MD5SumOK);
  j.at("MD5LinuxRoot").get_to(obj._MD5LinuxRoot);
  j.at("MD5App").get_to(obj._MD5App);
  j.at("MD5Calibration").get_to(obj._MD5Calibration);
  j.at("MD5Parameters").get_to(obj._MD5Parameters);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
