/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActivateEvaluationGroup.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/ActivateEvaluationGroup.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

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


} // namespace sick::multiScan200::v1_1_0::api::rest
