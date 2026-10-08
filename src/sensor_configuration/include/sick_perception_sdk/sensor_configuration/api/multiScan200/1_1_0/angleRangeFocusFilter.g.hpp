/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file angleRangeFocusFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /angleRangeFocusFilter.
*/
struct angleRangeFocusFilter
{

  constexpr static const char* variableName = "angleRangeFocusFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the angle range focus filter settings.
   */
  struct Get
  {
    struct Response
    {
      struct focusRegion
      {
        enum class direction
        {
          Horizontal = 0,
          Vertical = 1,
        };

        focusRegion() = default;

        explicit focusRegion(bool enable, direction direction, NumericRange<int, -1800000, 1800000, -450000> thetaStart, NumericRange<int, -1800000, 1800000, 450000> thetaStop, NumericRange<int, -900000, 900000, -100000> phiStart, NumericRange<int, -900000, 900000, 100000> phiStop)
          : _enable(enable), _direction(direction), _thetaStart(thetaStart), _thetaStop(thetaStop), _phiStart(phiStart), _phiStop(phiStop)
        {}

        bool _enable;
        direction _direction;
        NumericRange<int, -1800000, 1800000, -450000> _thetaStart;
        NumericRange<int, -1800000, 1800000, 450000> _thetaStop;
        NumericRange<int, -900000, 900000, -100000> _phiStart;
        NumericRange<int, -900000, 900000, 100000> _phiStop;
      };

      Response() = default;

      explicit Response(bool enable, NumericRange<int, -1800000, 1800000, -900000> thetaStart, NumericRange<int, -1800000, 1800000, 900000> thetaStop, NumericRange<int, -900000, 900000, -250000> phiStart, NumericRange<int, -900000, 900000, 250000> phiStop, NumericRange<int, 1, 50, 1> thetaIndexIncrement, NumericRange<int, 1, 50, 1> phiIndexIncrement, focusRegion focusRegion)
        : _enable(enable), _thetaStart(thetaStart), _thetaStop(thetaStop), _phiStart(phiStart), _phiStop(phiStop), _thetaIndexIncrement(thetaIndexIncrement), _phiIndexIncrement(phiIndexIncrement), _focusRegion(focusRegion)
      {}

      bool _enable;
      NumericRange<int, -1800000, 1800000, -900000> _thetaStart;
      NumericRange<int, -1800000, 1800000, 900000> _thetaStop;
      NumericRange<int, -900000, 900000, -250000> _phiStart;
      NumericRange<int, -900000, 900000, 250000> _phiStop;
      NumericRange<int, 1, 50, 1> _thetaIndexIncrement;
      NumericRange<int, 1, 50, 1> _phiIndexIncrement;
      focusRegion _focusRegion;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the angle range focus filter settings.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      struct focusRegion
      {
        enum class direction
        {
          Horizontal = 0,
          Vertical = 1,
        };

        focusRegion() = default;

        explicit focusRegion(bool enable, direction direction, NumericRange<int, -1800000, 1800000, -450000> thetaStart, NumericRange<int, -1800000, 1800000, 450000> thetaStop, NumericRange<int, -900000, 900000, -100000> phiStart, NumericRange<int, -900000, 900000, 100000> phiStop)
          : _enable(enable), _direction(direction), _thetaStart(thetaStart), _thetaStop(thetaStop), _phiStart(phiStart), _phiStop(phiStop)
        {}

        bool _enable;
        direction _direction;
        NumericRange<int, -1800000, 1800000, -450000> _thetaStart;
        NumericRange<int, -1800000, 1800000, 450000> _thetaStop;
        NumericRange<int, -900000, 900000, -100000> _phiStart;
        NumericRange<int, -900000, 900000, 100000> _phiStop;
      };

      Request() = default;

      explicit Request(bool enable, NumericRange<int, -1800000, 1800000, -900000> thetaStart, NumericRange<int, -1800000, 1800000, 900000> thetaStop, NumericRange<int, -900000, 900000, -250000> phiStart, NumericRange<int, -900000, 900000, 250000> phiStop, NumericRange<int, 1, 50, 1> thetaIndexIncrement, NumericRange<int, 1, 50, 1> phiIndexIncrement, focusRegion focusRegion)
        : _enable(enable), _thetaStart(thetaStart), _thetaStop(thetaStop), _phiStart(phiStart), _phiStop(phiStop), _thetaIndexIncrement(thetaIndexIncrement), _phiIndexIncrement(phiIndexIncrement), _focusRegion(focusRegion)
      {}

      bool _enable;
      NumericRange<int, -1800000, 1800000, -900000> _thetaStart;
      NumericRange<int, -1800000, 1800000, 900000> _thetaStop;
      NumericRange<int, -900000, 900000, -250000> _phiStart;
      NumericRange<int, -900000, 900000, 250000> _phiStop;
      NumericRange<int, 1, 50, 1> _thetaIndexIncrement;
      NumericRange<int, 1, 50, 1> _phiIndexIncrement;
      focusRegion _focusRegion;
    };

  }; // struct Post

}; // struct angleRangeFocusFilter

} // namespace sick::multiScan200::v1_1_0::api::rest
