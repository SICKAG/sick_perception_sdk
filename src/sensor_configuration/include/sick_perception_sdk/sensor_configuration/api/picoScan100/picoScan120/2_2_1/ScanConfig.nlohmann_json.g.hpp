/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanConfig.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanConfig.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response::ScanRange::aRangeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"udiAngleRes", obj._udiAngleRes.value()},
      {"diStartAngle", obj._diStartAngle.value()},
      {"diStopAngle", obj._diStopAngle.value()},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response::ScanRange::aRangeItem& obj)
{
  j.at("udiAngleRes").get_to(obj._udiAngleRes);
  j.at("diStartAngle").get_to(obj._diStartAngle);
  j.at("diStopAngle").get_to(obj._diStopAngle);
}

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response::ScanRange const& obj)
{
  j = nlohmann::ordered_json{
      {"uiLength", obj._uiLength.value()},
      {"aRange", obj._aRange},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response::ScanRange& obj)
{
  j.at("uiLength").get_to(obj._uiLength);
  j.at("aRange").get_to(obj._aRange);
}

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"udiScanFreq", obj._udiScanFreq.value()},
      {"ScanRange", obj._ScanRange},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response& obj)
{
  j.at("udiScanFreq").get_to(obj._udiScanFreq);
  j.at("ScanRange").get_to(obj._ScanRange);
}


} // namespace sick::picoScan120::v2_2_1::api::rest
