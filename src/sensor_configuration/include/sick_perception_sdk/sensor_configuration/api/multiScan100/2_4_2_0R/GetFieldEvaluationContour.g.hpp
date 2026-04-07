/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetFieldEvaluationContour.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /GetFieldEvaluationContour.
*/
struct GetFieldEvaluationContour
{

  constexpr static const char* methodName = "GetFieldEvaluationContour";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns the contour of an existing field.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint16_t EvaluationId)
        : _EvaluationId(EvaluationId)
      {}

      std::uint16_t _EvaluationId;
    };

    struct Response
    {
      struct ContourItem
      {
        struct PointsItem
        {
          PointsItem() = default;

          explicit PointsItem(std::int32_t x, std::int32_t y)
            : _x(x), _y(y)
          {}

          std::int32_t _x;
          std::int32_t _y;
        };

        ContourItem() = default;

        explicit ContourItem(std::uint16_t EvaluationId, std::vector<PointsItem> Points, NumericRange<std::int32_t, -100000, 100000, 0> LowerZLimit, NumericRange<std::int32_t, -100000, 100000, 0> UpperZLimit)
          : _EvaluationId(EvaluationId), _Points(Points), _LowerZLimit(std::move(LowerZLimit)), _UpperZLimit(std::move(UpperZLimit))
        {}

        std::uint16_t _EvaluationId;
        std::vector<PointsItem> _Points;
        NumericRange<std::int32_t, -100000, 100000, 0> _LowerZLimit;
        NumericRange<std::int32_t, -100000, 100000, 0> _UpperZLimit;
      };

      Response() = default;

      explicit Response(std::vector<ContourItem> Contour)
        : _Contour(Contour)
      {}

      std::vector<ContourItem> _Contour;
    };

  }; // struct Post

}; // struct GetFieldEvaluationContour

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
