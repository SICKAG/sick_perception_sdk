/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file perpendicularDistanceResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /perpendicularDistanceResult.
*/
struct perpendicularDistanceResult
{

  constexpr static const char* variableName = "perpendicularDistanceResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the perpendicular distance within a field.
   */
  struct Get
  {
    struct Response
    {
      struct evaluationsItem
      {
        struct minimumDistancePosition
        {
          minimumDistancePosition() = default;

          explicit minimumDistancePosition(NumericRange<std::int32_t, -500000, 500000, 0> x, NumericRange<std::int32_t, -500000, 500000, 0> y, NumericRange<std::int32_t, -500000, 500000, 0> z)
            : _x(std::move(x)), _y(std::move(y)), _z(std::move(z))
          {}

          NumericRange<std::int32_t, -500000, 500000, 0> _x;
          NumericRange<std::int32_t, -500000, 500000, 0> _y;
          NumericRange<std::int32_t, -500000, 500000, 0> _z;
        };

        struct maximumDistancePosition
        {
          maximumDistancePosition() = default;

          explicit maximumDistancePosition(NumericRange<std::int32_t, -500000, 500000, 0> x, NumericRange<std::int32_t, -500000, 500000, 0> y, NumericRange<std::int32_t, -500000, 500000, 0> z)
            : _x(std::move(x)), _y(std::move(y)), _z(std::move(z))
          {}

          NumericRange<std::int32_t, -500000, 500000, 0> _x;
          NumericRange<std::int32_t, -500000, 500000, 0> _y;
          NumericRange<std::int32_t, -500000, 500000, 0> _z;
        };

        evaluationsItem() = default;

        explicit evaluationsItem(std::uint16_t evaluationId, std::int32_t minimumDistance, std::int32_t maximumDistance, minimumDistancePosition minimumDistancePosition, maximumDistancePosition maximumDistancePosition)
          : _evaluationId(evaluationId), _minimumDistance(minimumDistance), _maximumDistance(maximumDistance), _minimumDistancePosition(minimumDistancePosition), _maximumDistancePosition(maximumDistancePosition)
        {}

        std::uint16_t _evaluationId;
        std::int32_t _minimumDistance;
        std::int32_t _maximumDistance;
        minimumDistancePosition _minimumDistancePosition;
        maximumDistancePosition _maximumDistancePosition;
      };

      Response() = default;

      explicit Response(std::uint64_t timestamp, std::vector<evaluationsItem> evaluations)
        : _timestamp(timestamp), _evaluations(evaluations)
      {}

      std::uint64_t _timestamp;
      std::vector<evaluationsItem> _evaluations;
    };

  }; // struct Get

}; // struct perpendicularDistanceResult

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
