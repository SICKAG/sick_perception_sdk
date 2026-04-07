/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DateTime.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DateTime.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, DateTime::Get::Response::DateTime const& obj)
{
  j = nlohmann::ordered_json{
      {"uiYear", obj._uiYear.value()},
      {"usiMonth", obj._usiMonth.value()},
      {"usiDay", obj._usiDay.value()},
      {"usiHour", obj._usiHour.value()},
      {"usiMinute", obj._usiMinute.value()},
      {"usiSec", obj._usiSec.value()},
      {"udiUSec", obj._udiUSec.value()},
  };
}

inline void from_json(const nlohmann::json& j, DateTime::Get::Response::DateTime& obj)
{
  j.at("uiYear").get_to(obj._uiYear);
  j.at("usiMonth").get_to(obj._usiMonth);
  j.at("usiDay").get_to(obj._usiDay);
  j.at("usiHour").get_to(obj._usiHour);
  j.at("usiMinute").get_to(obj._usiMinute);
  j.at("usiSec").get_to(obj._usiSec);
  j.at("udiUSec").get_to(obj._udiUSec);
}

inline void to_json(nlohmann::ordered_json& j, DateTime::Get::Response const& obj)
{
  j = obj._DateTime;
}

inline void from_json(const nlohmann::json& j, DateTime::Get::Response& obj)
{
  j.get_to(obj._DateTime);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
