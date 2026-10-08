/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetFieldEvaluationContour.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

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

        explicit PointsItem(int x, int y)
          : _x(x), _y(y)
        {}

        int _x;
        int _y;
      };

      Request() = default;

      explicit Request(int EvaluationId, std::vector<PointsItem> Points, NumericRange<int, -100000, 100000, 0> LowerZLimit, NumericRange<int, -100000, 100000, 0> UpperZLimit)
        : _EvaluationId(EvaluationId), _Points(Points), _LowerZLimit(LowerZLimit), _UpperZLimit(UpperZLimit)
      {}

      int _EvaluationId;
      std::vector<PointsItem> _Points;
      NumericRange<int, -100000, 100000, 0> _LowerZLimit;
      NumericRange<int, -100000, 100000, 0> _UpperZLimit;
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

} // namespace sick::multiScan200::v1_1_0::api::rest
