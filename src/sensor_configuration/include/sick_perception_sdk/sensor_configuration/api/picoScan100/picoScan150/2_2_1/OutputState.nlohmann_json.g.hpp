/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file OutputState.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/OutputState.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, OutputState::Get::Response::aDigitalOutItem::IOState const& obj)
{
  j = nlohmann::ordered_json{
      {"eIOState", obj._eIOState},
  };
}

inline void from_json(const nlohmann::json& j, OutputState::Get::Response::aDigitalOutItem::IOState& obj)
{
  j.at("eIOState").get_to(obj._eIOState);
}

inline void to_json(nlohmann::ordered_json& j, OutputState::Get::Response::aDigitalOutItem const& obj)
{
  j = nlohmann::ordered_json{
      {"IOState", obj._IOState},
      {"udiCounter", obj._udiCounter},
  };
}

inline void from_json(const nlohmann::json& j, OutputState::Get::Response::aDigitalOutItem& obj)
{
  j.at("IOState").get_to(obj._IOState);
  j.at("udiCounter").get_to(obj._udiCounter);
}

inline void to_json(nlohmann::ordered_json& j, OutputState::Get::Response::aTimeBlockItem const& obj)
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

inline void from_json(const nlohmann::json& j, OutputState::Get::Response::aTimeBlockItem& obj)
{
  j.at("uiYear").get_to(obj._uiYear);
  j.at("usiMonth").get_to(obj._usiMonth);
  j.at("usiDay").get_to(obj._usiDay);
  j.at("usiHour").get_to(obj._usiHour);
  j.at("usiMinute").get_to(obj._usiMinute);
  j.at("usiSec").get_to(obj._usiSec);
  j.at("udiUSec").get_to(obj._udiUSec);
}

inline void to_json(nlohmann::ordered_json& j, OutputState::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"uiVersionNumber", obj._uiVersionNumber},
      {"udiSystCount", obj._udiSystCount},
      {"aDigitalOut", obj._aDigitalOut},
      {"aTimeBlock", obj._aTimeBlock},
  };
}

inline void from_json(const nlohmann::json& j, OutputState::Get::Response& obj)
{
  j.at("uiVersionNumber").get_to(obj._uiVersionNumber);
  j.at("udiSystCount").get_to(obj._udiSystCount);
  j.at("aDigitalOut").get_to(obj._aDigitalOut);
  j.at("aTimeBlock").get_to(obj._aTimeBlock);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
