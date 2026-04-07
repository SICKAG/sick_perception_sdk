/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DataOutputRange.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DataOutputRange.
*/
struct DataOutputRange
{

  constexpr static const char* variableName = "DataOutputRange";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Select the start and stop angle of the measurement data output for the currently active configuration. Once a valid configuration is set, the device will transmit valid distance values between the selected start and stop angle and for all other angles zero values. The amount of transmitted data will not be reduced by using this function.
   */
  struct Get
  {
    struct Response
    {
      struct aRangeItem
      {
        aRangeItem() = default;

        explicit aRangeItem(NumericRange<std::uint32_t, 200, 4800, 1200> udiAngleRes, NumericRange<std::int32_t, -1800000, 1800000, -1800000> diStartAngle, NumericRange<std::int32_t, -1800000, 1800000, 1800000> diStopAngle)
          : _udiAngleRes(std::move(udiAngleRes)), _diStartAngle(std::move(diStartAngle)), _diStopAngle(std::move(diStopAngle))
        {}

        NumericRange<std::uint32_t, 200, 4800, 1200> _udiAngleRes;
        NumericRange<std::int32_t, -1800000, 1800000, -1800000> _diStartAngle;
        NumericRange<std::int32_t, -1800000, 1800000, 1800000> _diStopAngle;
      };

      Response() = default;

      explicit Response(NumericRange<std::uint16_t, 1, 1, 1> uiLength, std::array<aRangeItem, 1> aRange)
        : _uiLength(std::move(uiLength)), _aRange(aRange)
      {}

      NumericRange<std::uint16_t, 1, 1, 1> _uiLength;
      std::array<aRangeItem, 1> _aRange;
    };

  }; // struct Get

  /**
   * @brief Select the start and stop angle of the measurement data output for the currently active configuration. Once a valid configuration is set, the device will transmit valid distance values between the selected start and stop angle and for all other angles zero values. The amount of transmitted data will not be reduced by using this function.
   */
  struct Post
  {
    struct Request
    {
      struct aRangeItem
      {
        aRangeItem() = default;

        explicit aRangeItem(NumericRange<std::uint32_t, 200, 4800, 1200> udiAngleRes, NumericRange<std::int32_t, -1800000, 1800000, -1800000> diStartAngle, NumericRange<std::int32_t, -1800000, 1800000, 1800000> diStopAngle)
          : _udiAngleRes(std::move(udiAngleRes)), _diStartAngle(std::move(diStartAngle)), _diStopAngle(std::move(diStopAngle))
        {}

        NumericRange<std::uint32_t, 200, 4800, 1200> _udiAngleRes;
        NumericRange<std::int32_t, -1800000, 1800000, -1800000> _diStartAngle;
        NumericRange<std::int32_t, -1800000, 1800000, 1800000> _diStopAngle;
      };

      Request() = default;

      explicit Request(NumericRange<std::uint16_t, 1, 1, 1> uiLength, std::array<aRangeItem, 1> aRange)
        : _uiLength(std::move(uiLength)), _aRange(aRange)
      {}

      NumericRange<std::uint16_t, 1, 1, 1> _uiLength;
      std::array<aRangeItem, 1> _aRange;
    };

  }; // struct Post

}; // struct DataOutputRange

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
