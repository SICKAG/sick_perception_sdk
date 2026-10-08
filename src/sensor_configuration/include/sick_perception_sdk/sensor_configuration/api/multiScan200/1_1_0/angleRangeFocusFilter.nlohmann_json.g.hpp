/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file angleRangeFocusFilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/angleRangeFocusFilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, angleRangeFocusFilter::Get::Response::focusRegion const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"direction", obj._direction},
      {"thetaStart", obj._thetaStart.value()},
      {"thetaStop", obj._thetaStop.value()},
      {"phiStart", obj._phiStart.value()},
      {"phiStop", obj._phiStop.value()},
  };
}

inline void from_json(const nlohmann::json& j, angleRangeFocusFilter::Get::Response::focusRegion& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("direction").get_to(obj._direction);
  j.at("thetaStart").get_to(obj._thetaStart);
  j.at("thetaStop").get_to(obj._thetaStop);
  j.at("phiStart").get_to(obj._phiStart);
  j.at("phiStop").get_to(obj._phiStop);
}

inline void to_json(nlohmann::ordered_json& j, angleRangeFocusFilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"thetaStart", obj._thetaStart.value()},
      {"thetaStop", obj._thetaStop.value()},
      {"phiStart", obj._phiStart.value()},
      {"phiStop", obj._phiStop.value()},
      {"thetaIndexIncrement", obj._thetaIndexIncrement.value()},
      {"phiIndexIncrement", obj._phiIndexIncrement.value()},
      {"focusRegion", obj._focusRegion},
  };
}

inline void from_json(const nlohmann::json& j, angleRangeFocusFilter::Get::Response& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("thetaStart").get_to(obj._thetaStart);
  j.at("thetaStop").get_to(obj._thetaStop);
  j.at("phiStart").get_to(obj._phiStart);
  j.at("phiStop").get_to(obj._phiStop);
  j.at("thetaIndexIncrement").get_to(obj._thetaIndexIncrement);
  j.at("phiIndexIncrement").get_to(obj._phiIndexIncrement);
  j.at("focusRegion").get_to(obj._focusRegion);
}


inline void to_json(nlohmann::ordered_json& j, angleRangeFocusFilter::Post::Request::focusRegion const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"direction", obj._direction},
      {"thetaStart", obj._thetaStart.value()},
      {"thetaStop", obj._thetaStop.value()},
      {"phiStart", obj._phiStart.value()},
      {"phiStop", obj._phiStop.value()},
  };
}

inline void from_json(const nlohmann::json& j, angleRangeFocusFilter::Post::Request::focusRegion& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("direction").get_to(obj._direction);
  j.at("thetaStart").get_to(obj._thetaStart);
  j.at("thetaStop").get_to(obj._thetaStop);
  j.at("phiStart").get_to(obj._phiStart);
  j.at("phiStop").get_to(obj._phiStop);
}

inline void to_json(nlohmann::ordered_json& j, angleRangeFocusFilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"enable", obj._enable},
      {"thetaStart", obj._thetaStart.value()},
      {"thetaStop", obj._thetaStop.value()},
      {"phiStart", obj._phiStart.value()},
      {"phiStop", obj._phiStop.value()},
      {"thetaIndexIncrement", obj._thetaIndexIncrement.value()},
      {"phiIndexIncrement", obj._phiIndexIncrement.value()},
      {"focusRegion", obj._focusRegion},
  };
}

inline void from_json(const nlohmann::json& j, angleRangeFocusFilter::Post::Request& obj)
{
  j.at("enable").get_to(obj._enable);
  j.at("thetaStart").get_to(obj._thetaStart);
  j.at("thetaStop").get_to(obj._thetaStop);
  j.at("phiStart").get_to(obj._phiStart);
  j.at("phiStop").get_to(obj._phiStop);
  j.at("thetaIndexIncrement").get_to(obj._thetaIndexIncrement);
  j.at("phiIndexIncrement").get_to(obj._phiIndexIncrement);
  j.at("focusRegion").get_to(obj._focusRegion);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
