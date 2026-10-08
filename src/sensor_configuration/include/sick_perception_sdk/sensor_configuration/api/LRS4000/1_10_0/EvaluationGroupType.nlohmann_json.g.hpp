/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationGroupType.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EvaluationGroupType.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_10_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, EvaluationGroupType::Get::Response const& obj)
{
  j = obj._EvaluationGroupType;
}

inline void from_json(const nlohmann::json& j, EvaluationGroupType::Get::Response& obj)
{
  j.get_to(obj._EvaluationGroupType);
}


inline void to_json(nlohmann::ordered_json& j, EvaluationGroupType::Post::Request const& obj)
{
  j = obj._EvaluationGroupType;
}

inline void from_json(const nlohmann::json& j, EvaluationGroupType::Post::Request& obj)
{
  j.get_to(obj._EvaluationGroupType);
}


} // namespace sick::LRS4000::v1_10_0::api::rest
