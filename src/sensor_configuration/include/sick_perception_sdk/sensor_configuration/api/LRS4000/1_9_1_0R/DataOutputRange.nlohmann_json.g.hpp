/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DataOutputRange.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DataOutputRange.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, DataOutputRange::Get::Response::aRangeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"udiAngleRes", obj._udiAngleRes.value()},
      {"diStartAngle", obj._diStartAngle.value()},
      {"diStopAngle", obj._diStopAngle.value()},
  };
}

inline void from_json(const nlohmann::json& j, DataOutputRange::Get::Response::aRangeItem& obj)
{
  j.at("udiAngleRes").get_to(obj._udiAngleRes);
  j.at("diStartAngle").get_to(obj._diStartAngle);
  j.at("diStopAngle").get_to(obj._diStopAngle);
}

inline void to_json(nlohmann::ordered_json& j, DataOutputRange::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"uiLength", obj._uiLength.value()},
      {"aRange", obj._aRange},
  };
}

inline void from_json(const nlohmann::json& j, DataOutputRange::Get::Response& obj)
{
  j.at("uiLength").get_to(obj._uiLength);
  j.at("aRange").get_to(obj._aRange);
}


inline void to_json(nlohmann::ordered_json& j, DataOutputRange::Post::Request::aRangeItem const& obj)
{
  j = nlohmann::ordered_json{
      {"udiAngleRes", obj._udiAngleRes.value()},
      {"diStartAngle", obj._diStartAngle.value()},
      {"diStopAngle", obj._diStopAngle.value()},
  };
}

inline void from_json(const nlohmann::json& j, DataOutputRange::Post::Request::aRangeItem& obj)
{
  j.at("udiAngleRes").get_to(obj._udiAngleRes);
  j.at("diStartAngle").get_to(obj._diStartAngle);
  j.at("diStopAngle").get_to(obj._diStopAngle);
}

inline void to_json(nlohmann::ordered_json& j, DataOutputRange::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"uiLength", obj._uiLength.value()},
      {"aRange", obj._aRange},
  };
}

inline void from_json(const nlohmann::json& j, DataOutputRange::Post::Request& obj)
{
  j.at("uiLength").get_to(obj._uiLength);
  j.at("aRange").get_to(obj._aRange);
}


} // namespace sick::LRS4000::v1_9_1_0R::api::rest
