/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationConfigState.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/EvaluationConfigState.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, EvaluationConfigState::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"ActiveBeamsLimit", obj._ActiveBeamsLimit},
      {"ActiveEvaluationsLimit", obj._ActiveEvaluationsLimit},
      {"ActiveBeamsPerEvaluationLimit", obj._ActiveBeamsPerEvaluationLimit},
      {"NumberOfIntersectingBeams", obj._NumberOfIntersectingBeams},
      {"InputIsOutputErrorList", obj._InputIsOutputErrorList},
  };
}

inline void from_json(const nlohmann::json& j, EvaluationConfigState::Get::Response& obj)
{
  j.at("ActiveBeamsLimit").get_to(obj._ActiveBeamsLimit);
  j.at("ActiveEvaluationsLimit").get_to(obj._ActiveEvaluationsLimit);
  j.at("ActiveBeamsPerEvaluationLimit").get_to(obj._ActiveBeamsPerEvaluationLimit);
  j.at("NumberOfIntersectingBeams").get_to(obj._NumberOfIntersectingBeams);
  j.at("InputIsOutputErrorList").get_to(obj._InputIsOutputErrorList);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
