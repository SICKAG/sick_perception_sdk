/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPangleRangeFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/LFPangleRangeFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPangleRangeFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"fThetaStart", obj._fThetaStart.value()},
      {"fThetaStop", obj._fThetaStop.value()},
      {"fPhiStart", obj._fPhiStart.value()},
      {"fPhiStop", obj._fPhiStop.value()},
      {"uiBeamIncrement", obj._uiBeamIncrement.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPangleRangeFilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("fThetaStart").get_to(obj._fThetaStart);
  j.at("fThetaStop").get_to(obj._fThetaStop);
  j.at("fPhiStart").get_to(obj._fPhiStart);
  j.at("fPhiStop").get_to(obj._fPhiStop);
  j.at("uiBeamIncrement").get_to(obj._uiBeamIncrement);
}


inline void to_json(nlohmann::ordered_json& j, LFPangleRangeFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"fThetaStart", obj._fThetaStart.value()},
      {"fThetaStop", obj._fThetaStop.value()},
      {"fPhiStart", obj._fPhiStart.value()},
      {"fPhiStop", obj._fPhiStop.value()},
      {"uiBeamIncrement", obj._uiBeamIncrement.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPangleRangeFilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("fThetaStart").get_to(obj._fThetaStart);
  j.at("fThetaStop").get_to(obj._fThetaStop);
  j.at("fPhiStart").get_to(obj._fPhiStart);
  j.at("fPhiStop").get_to(obj._fPhiStop);
  j.at("uiBeamIncrement").get_to(obj._uiBeamIncrement);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
