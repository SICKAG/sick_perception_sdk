/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetFieldEvaluationConfiguration.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/SetFieldEvaluationConfiguration.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsMaskBasedItem const& obj)
{
  j = nlohmann::ordered_json{
      {"InfringementThresholdFactor", obj._InfringementThresholdFactor.value()},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsMaskBasedItem& obj)
{
  j.at("InfringementThresholdFactor").get_to(obj._InfringementThresholdFactor);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsSegmentationBasedItem const& obj)
{
  j = nlohmann::ordered_json{
      {"SampleParam1", obj._SampleParam1},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsSegmentationBasedItem& obj)
{
  j.at("SampleParam1").get_to(obj._SampleParam1);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsCommonItem const& obj)
{
  j = nlohmann::ordered_json{
      {"MinimumObjectSizeHorizontal", obj._MinimumObjectSizeHorizontal.value()},
      {"MinimumObjectSizeVertical", obj._MinimumObjectSizeVertical.value()},
      {"OcclusionHandling", obj._OcclusionHandling},
      {"TreatMissingDataAsInfringed", obj._TreatMissingDataAsInfringed},
      {"TimeForInfringedState", obj._TimeForInfringedState.value()},
      {"TimeForFreeState", obj._TimeForFreeState.value()},
      {"Reserved3", obj._Reserved3},
      {"Reserved4", obj._Reserved4},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsCommonItem& obj)
{
  j.at("MinimumObjectSizeHorizontal").get_to(obj._MinimumObjectSizeHorizontal);
  j.at("MinimumObjectSizeVertical").get_to(obj._MinimumObjectSizeVertical);
  j.at("OcclusionHandling").get_to(obj._OcclusionHandling);
  j.at("TreatMissingDataAsInfringed").get_to(obj._TreatMissingDataAsInfringed);
  j.at("TimeForInfringedState").get_to(obj._TimeForInfringedState);
  j.at("TimeForFreeState").get_to(obj._TimeForFreeState);
  j.at("Reserved3").get_to(obj._Reserved3);
  j.at("Reserved4").get_to(obj._Reserved4);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsExitSizeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"disableExitSize", obj._disableExitSize},
      {"exitSizeVertical", obj._exitSizeVertical.value()},
      {"exitSizeHorizontal", obj._exitSizeHorizontal.value()},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration::EvaluationParamsExitSizeItem& obj)
{
  j.at("disableExitSize").get_to(obj._disableExitSize);
  j.at("exitSizeVertical").get_to(obj._exitSizeVertical);
  j.at("exitSizeHorizontal").get_to(obj._exitSizeHorizontal);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration const& obj)
{
  j = nlohmann::ordered_json{
      {"Version", obj._Version},
      {"Source", obj._Source},
      {"Name", obj._Name},
      {"ID", obj._ID},
      {"EvaluationParamsMaskBased", obj._EvaluationParamsMaskBased},
      {"EvaluationParamsSegmentationBased", obj._EvaluationParamsSegmentationBased},
      {"EvaluationParamsCommon", obj._EvaluationParamsCommon},
      {"EvaluationParamsExitSize", obj._EvaluationParamsExitSize},
      {"VolumeList", obj._VolumeList},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request::Configuration& obj)
{
  j.at("Version").get_to(obj._Version);
  j.at("Source").get_to(obj._Source);
  j.at("Name").get_to(obj._Name);
  j.at("ID").get_to(obj._ID);
  j.at("EvaluationParamsMaskBased").get_to(obj._EvaluationParamsMaskBased);
  j.at("EvaluationParamsSegmentationBased").get_to(obj._EvaluationParamsSegmentationBased);
  j.at("EvaluationParamsCommon").get_to(obj._EvaluationParamsCommon);
  j.at("EvaluationParamsExitSize").get_to(obj._EvaluationParamsExitSize);
  j.at("VolumeList").get_to(obj._VolumeList);
}

inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"EvaluationId", obj._EvaluationId},
      {"Name", obj._Name},
      {"Configuration", obj._Configuration},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Request& obj)
{
  j.at("EvaluationId").get_to(obj._EvaluationId);
  j.at("Name").get_to(obj._Name);
  j.at("Configuration").get_to(obj._Configuration);
}


inline void to_json(nlohmann::ordered_json& j, SetFieldEvaluationConfiguration::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"ErrorCode", obj._ErrorCode},
  };
}

inline void from_json(const nlohmann::json& j, SetFieldEvaluationConfiguration::Post::Response& obj)
{
  j.at("ErrorCode").get_to(obj._ErrorCode);
}


} // namespace sick::multiScan200::v1_1_0::api::rest
