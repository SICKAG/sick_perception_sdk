/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file compactTelegramType6Content.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/compactTelegramType6Content.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, compactTelegramType6Content::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"includeRssi", obj._includeRssi},
      {"includeProperties", obj._includeProperties},
      {"includeAmbientLight", obj._includeAmbientLight},
      {"reserved", obj._reserved},
  };
}

inline void from_json(const nlohmann::json& j, compactTelegramType6Content::Get::Response& obj)
{
  j.at("includeRssi").get_to(obj._includeRssi);
  j.at("includeProperties").get_to(obj._includeProperties);
  j.at("includeAmbientLight").get_to(obj._includeAmbientLight);
  j.at("reserved").get_to(obj._reserved);
}


inline void to_json(nlohmann::ordered_json& j, compactTelegramType6Content::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"includeRssi", obj._includeRssi},
      {"includeProperties", obj._includeProperties},
      {"includeAmbientLight", obj._includeAmbientLight},
      {"reserved", obj._reserved},
  };
}

inline void from_json(const nlohmann::json& j, compactTelegramType6Content::Post::Request& obj)
{
  j.at("includeRssi").get_to(obj._includeRssi);
  j.at("includeProperties").get_to(obj._includeProperties);
  j.at("includeAmbientLight").get_to(obj._includeAmbientLight);
  j.at("reserved").get_to(obj._reserved);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
