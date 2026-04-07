/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetFieldEvaluationContour.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetFieldEvaluationContour.
*/
struct SetFieldEvaluationContour
{

  constexpr static const char* methodName = "SetFieldEvaluationContour";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the contour of an existing field.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
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

      Request() = default;

      explicit Request(std::uint16_t EvaluationId, std::vector<PointsItem> Points, NumericRange<std::int32_t, -100000, 100000, 0> LowerZLimit, NumericRange<std::int32_t, -100000, 100000, 0> UpperZLimit)
        : _EvaluationId(EvaluationId), _Points(Points), _LowerZLimit(std::move(LowerZLimit)), _UpperZLimit(std::move(UpperZLimit))
      {}

      std::uint16_t _EvaluationId;
      std::vector<PointsItem> _Points;
      NumericRange<std::int32_t, -100000, 100000, 0> _LowerZLimit;
      NumericRange<std::int32_t, -100000, 100000, 0> _UpperZLimit;
    };

    struct Response
    {
      enum class ErrorCode
      {
        SopasErrNoErr = 0,
        SopasErrInvalidEvaluationId = 1,
        SopasErrInvalidPolygon = 2,
        SopasErrInvalidZlim = 3,
      };

      Response() = default;

      explicit Response(ErrorCode ErrorCode)
        : _ErrorCode(ErrorCode)
      {}

      ErrorCode _ErrorCode;
    };

  }; // struct Post

}; // struct SetFieldEvaluationContour

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
