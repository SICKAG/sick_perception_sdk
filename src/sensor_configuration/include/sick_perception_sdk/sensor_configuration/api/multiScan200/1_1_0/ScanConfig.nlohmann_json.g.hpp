/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanConfig.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/ScanConfig.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response::ScanRange::aThetaAngleRangeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"udiThetaAngleRes", obj._udiThetaAngleRes.value()},
      {"diThetaStartAngle", obj._diThetaStartAngle.value()},
      {"diThetaStopAngle", obj._diThetaStopAngle.value()},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response::ScanRange::aThetaAngleRangeItem& obj)
{
  j.at("udiThetaAngleRes").get_to(obj._udiThetaAngleRes);
  j.at("diThetaStartAngle").get_to(obj._diThetaStartAngle);
  j.at("diThetaStopAngle").get_to(obj._diThetaStopAngle);
}

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response::ScanRange::aPhiAngleRangeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"udiPhiAngleRes", obj._udiPhiAngleRes.value()},
      {"diPhiStartAngle", obj._diPhiStartAngle.value()},
      {"diPhiStopAngle", obj._diPhiStopAngle.value()},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response::ScanRange::aPhiAngleRangeItem& obj)
{
  j.at("udiPhiAngleRes").get_to(obj._udiPhiAngleRes);
  j.at("diPhiStartAngle").get_to(obj._diPhiStartAngle);
  j.at("diPhiStopAngle").get_to(obj._diPhiStopAngle);
}

inline void to_json(nlohmann::ordered_json& j, ScanConfig::Get::Response::ScanRange const& obj)
{
  j = nlohmann::ordered_json{
      {"uiLength", obj._uiLength.value()},
      {"aThetaAngleRange", obj._aThetaAngleRange},
      {"aPhiAngleRange", obj._aPhiAngleRange},
  };
}

inline void from_json(const nlohmann::json& j, ScanConfig::Get::Response::ScanRange& obj)
{
  j.at("uiLength").get_to(obj._uiLength);
  j.at("aThetaAngleRange").get_to(obj._aThetaAngleRange);
  j.at("aPhiAngleRange").get_to(obj._aPhiAngleRange);
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


} // namespace sick::multiScan200::v1_1_0::api::rest
