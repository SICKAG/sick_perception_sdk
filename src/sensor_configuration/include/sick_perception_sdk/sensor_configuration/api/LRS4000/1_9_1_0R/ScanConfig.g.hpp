/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanConfig.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ScanConfig.
*/
struct ScanConfig
{

  constexpr static const char* variableName = "ScanConfig";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Configuration of angular resolution, scanning frequency, start- and stop angle.
   */
  struct Get
  {
    struct Response
    {
      struct ScanRange
      {
        struct aRangeItem
        {
          aRangeItem() = default;

          explicit aRangeItem(NumericRange<std::uint32_t, 200, 5000, 1200> udiAngleRes, NumericRange<std::int32_t, -1800000, 1800000, -1800000> diStartAngle, NumericRange<std::int32_t, -1800000, 1800000, 1800000> diStopAngle)
            : _udiAngleRes(std::move(udiAngleRes)), _diStartAngle(std::move(diStartAngle)), _diStopAngle(std::move(diStopAngle))
          {}

          NumericRange<std::uint32_t, 200, 5000, 1200> _udiAngleRes;
          NumericRange<std::int32_t, -1800000, 1800000, -1800000> _diStartAngle;
          NumericRange<std::int32_t, -1800000, 1800000, 1800000> _diStopAngle;
        };

        ScanRange() = default;

        explicit ScanRange(NumericRange<std::uint16_t, 1, 1, 1> uiLength, std::array<aRangeItem, 1> aRange)
          : _uiLength(std::move(uiLength)), _aRange(aRange)
        {}

        NumericRange<std::uint16_t, 1, 1, 1> _uiLength;
        std::array<aRangeItem, 1> _aRange;
      };

      Response() = default;

      explicit Response(NumericRange<std::uint32_t, 500, 2500, 1250> udiScanFreq, ScanRange ScanRange)
        : _udiScanFreq(std::move(udiScanFreq)), _ScanRange(ScanRange)
      {}

      NumericRange<std::uint32_t, 500, 2500, 1250> _udiScanFreq;
      ScanRange _ScanRange;
    };

  }; // struct Get

}; // struct ScanConfig

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
