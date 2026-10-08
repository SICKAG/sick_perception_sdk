/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file compactTelegramType1Content.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/compactTelegramType1Content.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, compactTelegramType1Content::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"includeRssi", obj._includeRssi},
      {"includeProperties", obj._includeProperties},
  };
}

inline void from_json(const nlohmann::json& j, compactTelegramType1Content::Get::Response& obj)
{
  j.at("includeRssi").get_to(obj._includeRssi);
  j.at("includeProperties").get_to(obj._includeProperties);
}


inline void to_json(nlohmann::ordered_json& j, compactTelegramType1Content::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"includeRssi", obj._includeRssi},
      {"includeProperties", obj._includeProperties},
  };
}

inline void from_json(const nlohmann::json& j, compactTelegramType1Content::Post::Request& obj)
{
  j.at("includeRssi").get_to(obj._includeRssi);
  j.at("includeProperties").get_to(obj._includeProperties);
}


} // namespace sick::picoScan120::v2_3_3::api::rest
