/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InputState.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/InputState.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, InputState::Get::Response::aDigitalInItem::IOState const& obj)
{
  j = nlohmann::ordered_json{
      {"eIOState", obj._eIOState},
  };
}

inline void from_json(const nlohmann::json& j, InputState::Get::Response::aDigitalInItem::IOState& obj)
{
  j.at("eIOState").get_to(obj._eIOState);
}

inline void to_json(nlohmann::ordered_json& j, InputState::Get::Response::aDigitalInItem const& obj)
{
  j = nlohmann::ordered_json{
      {"IOState", obj._IOState},
  };
}

inline void from_json(const nlohmann::json& j, InputState::Get::Response::aDigitalInItem& obj)
{
  j.at("IOState").get_to(obj._IOState);
}

inline void to_json(nlohmann::ordered_json& j, InputState::Get::Response::aTimeBlockItem const& obj)
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

inline void from_json(const nlohmann::json& j, InputState::Get::Response::aTimeBlockItem& obj)
{
  j.at("uiYear").get_to(obj._uiYear);
  j.at("usiMonth").get_to(obj._usiMonth);
  j.at("usiDay").get_to(obj._usiDay);
  j.at("usiHour").get_to(obj._usiHour);
  j.at("usiMinute").get_to(obj._usiMinute);
  j.at("usiSec").get_to(obj._usiSec);
  j.at("udiUSec").get_to(obj._udiUSec);
}

inline void to_json(nlohmann::ordered_json& j, InputState::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"uiVersionNumber", obj._uiVersionNumber},
      {"udiSystCount", obj._udiSystCount},
      {"aDigitalIn", obj._aDigitalIn},
      {"aTimeBlock", obj._aTimeBlock},
  };
}

inline void from_json(const nlohmann::json& j, InputState::Get::Response& obj)
{
  j.at("uiVersionNumber").get_to(obj._uiVersionNumber);
  j.at("udiSystCount").get_to(obj._udiSystCount);
  j.at("aDigitalIn").get_to(obj._aDigitalIn);
  j.at("aTimeBlock").get_to(obj._aTimeBlock);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
