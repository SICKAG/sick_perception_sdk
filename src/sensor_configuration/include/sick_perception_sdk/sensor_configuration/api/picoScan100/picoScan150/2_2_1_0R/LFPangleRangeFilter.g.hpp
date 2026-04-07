/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPangleRangeFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPangleRangeFilter.
*/
struct LFPangleRangeFilter
{

  constexpr static const char* variableName = "LFPangleRangeFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the angle range filter settings. The filter restricts the output scan to a specified angle range. Filtered measurement values are set to 0. If the content of a complete data segment is set to 0, this segment is not output anymore.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::int32_t, -1380000, 1380000, -900000> fThetaStart, NumericRange<std::int32_t, -1380000, 1380000, 900000> fThetaStop, NumericRange<std::int32_t, -900000, 900000, -900000> fPhiStart, NumericRange<std::int32_t, -900000, 900000, 900000> fPhiStop, NumericRange<std::uint16_t, 1, 20, 1> uiBeamIncrement)
        : _bEnable(bEnable), _fThetaStart(std::move(fThetaStart)), _fThetaStop(std::move(fThetaStop)), _fPhiStart(std::move(fPhiStart)), _fPhiStop(std::move(fPhiStop)), _uiBeamIncrement(std::move(uiBeamIncrement))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -1380000, 1380000, -900000> _fThetaStart;
      NumericRange<std::int32_t, -1380000, 1380000, 900000> _fThetaStop;
      NumericRange<std::int32_t, -900000, 900000, -900000> _fPhiStart;
      NumericRange<std::int32_t, -900000, 900000, 900000> _fPhiStop;
      NumericRange<std::uint16_t, 1, 20, 1> _uiBeamIncrement;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the angle range filter settings. The filter restricts the output scan to a specified angle range. Filtered measurement values are set to 0. If the content of a complete data segment is set to 0, this segment is not output anymore.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::int32_t, -1380000, 1380000, -900000> fThetaStart, NumericRange<std::int32_t, -1380000, 1380000, 900000> fThetaStop, NumericRange<std::int32_t, -900000, 900000, -900000> fPhiStart, NumericRange<std::int32_t, -900000, 900000, 900000> fPhiStop, NumericRange<std::uint16_t, 1, 20, 1> uiBeamIncrement)
        : _bEnable(bEnable), _fThetaStart(std::move(fThetaStart)), _fThetaStop(std::move(fThetaStop)), _fPhiStart(std::move(fPhiStart)), _fPhiStop(std::move(fPhiStop)), _uiBeamIncrement(std::move(uiBeamIncrement))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -1380000, 1380000, -900000> _fThetaStart;
      NumericRange<std::int32_t, -1380000, 1380000, 900000> _fThetaStop;
      NumericRange<std::int32_t, -900000, 900000, -900000> _fPhiStart;
      NumericRange<std::int32_t, -900000, 900000, 900000> _fPhiStop;
      NumericRange<std::uint16_t, 1, 20, 1> _uiBeamIncrement;
    };

  }; // struct Post

}; // struct LFPangleRangeFilter

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
