/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file treatBlockedSectorsAsErrorSectors.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/treatBlockedSectorsAsErrorSectors.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

inline void to_json(nlohmann::ordered_json& j, treatBlockedSectorsAsErrorSectors::Get::Response const& obj)
{
  j = obj._treatBlockedSectorsAsErrorSectors;
}

inline void from_json(const nlohmann::json& j, treatBlockedSectorsAsErrorSectors::Get::Response& obj)
{
  j.get_to(obj._treatBlockedSectorsAsErrorSectors);
}


inline void to_json(nlohmann::ordered_json& j, treatBlockedSectorsAsErrorSectors::Post::Request const& obj)
{
  j = obj._treatBlockedSectorsAsErrorSectors;
}

inline void from_json(const nlohmann::json& j, treatBlockedSectorsAsErrorSectors::Post::Request& obj)
{
  j.get_to(obj._treatBlockedSectorsAsErrorSectors);
}


} // namespace sick::picoScan150::v2_3_3::api::rest
