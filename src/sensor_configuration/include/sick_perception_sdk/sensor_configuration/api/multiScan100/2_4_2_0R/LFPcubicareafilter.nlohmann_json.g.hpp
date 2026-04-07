/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPcubicareafilter.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPcubicareafilter.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, LFPcubicareafilter::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"lXMin", obj._lXMin.value()},
      {"lXMax", obj._lXMax.value()},
      {"lYMin", obj._lYMin.value()},
      {"lYMax", obj._lYMax.value()},
      {"lZMin", obj._lZMin.value()},
      {"lZMax", obj._lZMax.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPcubicareafilter::Get::Response& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("lXMin").get_to(obj._lXMin);
  j.at("lXMax").get_to(obj._lXMax);
  j.at("lYMin").get_to(obj._lYMin);
  j.at("lYMax").get_to(obj._lYMax);
  j.at("lZMin").get_to(obj._lZMin);
  j.at("lZMax").get_to(obj._lZMax);
}


inline void to_json(nlohmann::ordered_json& j, LFPcubicareafilter::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"bEnable", obj._bEnable},
      {"lXMin", obj._lXMin.value()},
      {"lXMax", obj._lXMax.value()},
      {"lYMin", obj._lYMin.value()},
      {"lYMax", obj._lYMax.value()},
      {"lZMin", obj._lZMin.value()},
      {"lZMax", obj._lZMax.value()},
  };
}

inline void from_json(const nlohmann::json& j, LFPcubicareafilter::Post::Request& obj)
{
  j.at("bEnable").get_to(obj._bEnable);
  j.at("lXMin").get_to(obj._lXMin);
  j.at("lXMax").get_to(obj._lXMax);
  j.at("lYMin").get_to(obj._lYMin);
  j.at("lYMax").get_to(obj._lYMax);
  j.at("lZMin").get_to(obj._lZMin);
  j.at("lZMax").get_to(obj._lZMax);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
