/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActivateEvaluationGroup.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ActivateEvaluationGroup.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, ActivateEvaluationGroup::Post::Request::ListItem const& obj)
{
  j = nlohmann::ordered_json{
      {"GroupId", obj._GroupId.value()},
      {"Activate", obj._Activate},
  };
}

inline void from_json(const nlohmann::json& j, ActivateEvaluationGroup::Post::Request::ListItem& obj)
{
  j.at("GroupId").get_to(obj._GroupId);
  j.at("Activate").get_to(obj._Activate);
}

inline void to_json(nlohmann::ordered_json& j, ActivateEvaluationGroup::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"List", obj._List},
  };
}

inline void from_json(const nlohmann::json& j, ActivateEvaluationGroup::Post::Request& obj)
{
  j.at("List").get_to(obj._List);
}


inline void to_json(nlohmann::ordered_json& j, ActivateEvaluationGroup::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"Success", obj._Success},
  };
}

inline void from_json(const nlohmann::json& j, ActivateEvaluationGroup::Post::Response& obj)
{
  j.at("Success").get_to(obj._Success);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
