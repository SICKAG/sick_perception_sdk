/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetFieldEvaluationContour.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1_0R/SetFieldEvaluationContour.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationContour::Post::Request::PointsItem const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x},
      {"y", obj._y},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationContour::Post::Request::PointsItem& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationContour::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"EvaluationId", obj._EvaluationId},
      {"Points", obj._Points},
      {"LowerZLimit", obj._LowerZLimit.value()},
      {"UpperZLimit", obj._UpperZLimit.value()},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationContour::Post::Request& obj)
{
  j.at("EvaluationId").get_to(obj._EvaluationId);
  j.at("Points").get_to(obj._Points);
  j.at("LowerZLimit").get_to(obj._LowerZLimit);
  j.at("UpperZLimit").get_to(obj._UpperZLimit);
}


inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationContour::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"ErrorCode", obj._ErrorCode},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationContour::Post::Response& obj)
{
  j.at("ErrorCode").get_to(obj._ErrorCode);
}


} // namespace sick::picoScan150::v2_2_1_0R::api::rest
