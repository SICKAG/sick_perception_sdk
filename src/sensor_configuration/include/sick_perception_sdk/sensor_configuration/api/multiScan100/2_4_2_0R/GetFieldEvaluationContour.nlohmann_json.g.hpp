/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetFieldEvaluationContour.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/GetFieldEvaluationContour.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, GetFieldEvaluationContour::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"EvaluationId", obj._EvaluationId},
  };
}

inline void from_json(const nlohmann::json& j, GetFieldEvaluationContour::Post::Request& obj)
{
  j.at("EvaluationId").get_to(obj._EvaluationId);
}


inline void to_json(nlohmann::ordered_json& j, GetFieldEvaluationContour::Post::Response::ContourItem::PointsItem const& obj)
{
  j = nlohmann::ordered_json{
      {"x", obj._x},
      {"y", obj._y},
  };
}

inline void from_json(const nlohmann::json& j, GetFieldEvaluationContour::Post::Response::ContourItem::PointsItem& obj)
{
  j.at("x").get_to(obj._x);
  j.at("y").get_to(obj._y);
}

inline void to_json(nlohmann::ordered_json& j, GetFieldEvaluationContour::Post::Response::ContourItem const& obj)
{
  j = nlohmann::ordered_json{
      {"EvaluationId", obj._EvaluationId},
      {"Points", obj._Points},
      {"LowerZLimit", obj._LowerZLimit.value()},
      {"UpperZLimit", obj._UpperZLimit.value()},
  };
}

inline void from_json(const nlohmann::json& j, GetFieldEvaluationContour::Post::Response::ContourItem& obj)
{
  j.at("EvaluationId").get_to(obj._EvaluationId);
  j.at("Points").get_to(obj._Points);
  j.at("LowerZLimit").get_to(obj._LowerZLimit);
  j.at("UpperZLimit").get_to(obj._UpperZLimit);
}

inline void to_json(nlohmann::ordered_json& j, GetFieldEvaluationContour::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Contour", obj._Contour},
  };
}

inline void from_json(const nlohmann::json& j, GetFieldEvaluationContour::Post::Response& obj)
{
  j.at("Contour").get_to(obj._Contour);
}


} // namespace sick::multiScan100::v2_4_2_0R::api::rest
