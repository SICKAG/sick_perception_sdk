/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/FieldEvaluationResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem::PositionsItem const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x},
      {"y", obj._y},
  };
}

inline void from_json(const nlohmann::json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem::PositionsItem& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
}

inline void to_json(nlohmann::ordered_json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem const& obj)
{
  j = nlohmann::ordered_json{
      {"State", obj._State},
      {"Positions", obj._Positions},
  };
}

inline void from_json(const nlohmann::json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem& obj)
{
  j.at("State").get_to(obj._State);
  j.at("Positions").get_to(obj._Positions);
}

inline void to_json(nlohmann::ordered_json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult const& obj)
{
  j = nlohmann::ordered_json{
      {"Version", obj._Version},
      {"Timestamp", obj._Timestamp},
      {"EvaluationResultList", obj._EvaluationResultList},
  };
}

inline void from_json(const nlohmann::json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult& obj)
{
  j.at("Version").get_to(obj._Version);
  j.at("Timestamp").get_to(obj._Timestamp);
  j.at("EvaluationResultList").get_to(obj._EvaluationResultList);
}

inline void to_json(nlohmann::ordered_json& j, FieldEvaluationResult::Get::Response const& obj)
{
  j = obj._FieldEvaluationResult;
}

inline void from_json(const nlohmann::json& j, FieldEvaluationResult::Get::Response& obj)
{
  j.get_to(obj._FieldEvaluationResult);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
