/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file perpendicularDistanceResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/perpendicularDistanceResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, perpendicularDistanceResult::Get::Response::evaluationsItem::minimumDistancePosition const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x.value()},
      {"y", obj._y.value()},
      {"z", obj._z.value()},
  };
}

inline void from_json(const nlohmann::json& j, perpendicularDistanceResult::Get::Response::evaluationsItem::minimumDistancePosition& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
}

inline void to_json(nlohmann::ordered_json& j, perpendicularDistanceResult::Get::Response::evaluationsItem::maximumDistancePosition const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x.value()},
      {"y", obj._y.value()},
      {"z", obj._z.value()},
  };
}

inline void from_json(const nlohmann::json& j, perpendicularDistanceResult::Get::Response::evaluationsItem::maximumDistancePosition& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
  j.at("z").get_to(obj._z);
}

inline void to_json(nlohmann::ordered_json& j, perpendicularDistanceResult::Get::Response::evaluationsItem const& obj)
{
  j = nlohmann::ordered_json{
      {"evaluationId", obj._evaluationId},
      {"minimumDistance", obj._minimumDistance},
      {"maximumDistance", obj._maximumDistance},
      {"minimumDistancePosition", obj._minimumDistancePosition},
      {"maximumDistancePosition", obj._maximumDistancePosition},
  };
}

inline void from_json(const nlohmann::json& j, perpendicularDistanceResult::Get::Response::evaluationsItem& obj)
{
  j.at("evaluationId").get_to(obj._evaluationId);
  j.at("minimumDistance").get_to(obj._minimumDistance);
  j.at("maximumDistance").get_to(obj._maximumDistance);
  j.at("minimumDistancePosition").get_to(obj._minimumDistancePosition);
  j.at("maximumDistancePosition").get_to(obj._maximumDistancePosition);
}

inline void to_json(nlohmann::ordered_json& j, perpendicularDistanceResult::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"timestamp", obj._timestamp},
      {"evaluations", obj._evaluations},
  };
}

inline void from_json(const nlohmann::json& j, perpendicularDistanceResult::Get::Response& obj)
{
  j.at("timestamp").get_to(obj._timestamp);
  j.at("evaluations").get_to(obj._evaluations);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
