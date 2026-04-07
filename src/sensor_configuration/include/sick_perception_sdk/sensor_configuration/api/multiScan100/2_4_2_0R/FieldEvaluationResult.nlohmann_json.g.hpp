/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationResult.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FieldEvaluationResult.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem const& obj)
{
  j = nlohmann::ordered_json{
      {"State", obj._State},
  };
}

inline void from_json(const nlohmann::json& j, FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem& obj)
{
  j.at("State").get_to(obj._State);
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


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
