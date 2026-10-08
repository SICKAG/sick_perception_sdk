/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanConfig.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /ScanConfig.
*/
struct ScanConfig
{

  constexpr static const char* variableName = "ScanConfig";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the configuration of angular resolution, scanning frequency and start angle.
   */
  struct Get
  {
    struct Response
    {
      struct ScanRange
      {
        struct aThetaAngleRangeItem
        {
          aThetaAngleRangeItem() = default;

          explicit aThetaAngleRangeItem(NumericRange<int, 100, 100000, 4700> udiThetaAngleRes, NumericRange<int, -1800000, 1800000, -1380000> diThetaStartAngle, NumericRange<int, -1800000, 1800000, 1380000> diThetaStopAngle)
            : _udiThetaAngleRes(udiThetaAngleRes), _diThetaStartAngle(diThetaStartAngle), _diThetaStopAngle(diThetaStopAngle)
          {}

          NumericRange<int, 100, 100000, 4700> _udiThetaAngleRes;
          NumericRange<int, -1800000, 1800000, -1380000> _diThetaStartAngle;
          NumericRange<int, -1800000, 1800000, 1380000> _diThetaStopAngle;
        };

        struct aPhiAngleRangeItem
        {
          aPhiAngleRangeItem() = default;

          explicit aPhiAngleRangeItem(NumericRange<int, 100, 100000, 4700> udiPhiAngleRes, NumericRange<int, -450000, 450000, -225000> diPhiStartAngle, NumericRange<int, -450000, 450000, 225000> diPhiStopAngle)
            : _udiPhiAngleRes(udiPhiAngleRes), _diPhiStartAngle(diPhiStartAngle), _diPhiStopAngle(diPhiStopAngle)
          {}

          NumericRange<int, 100, 100000, 4700> _udiPhiAngleRes;
          NumericRange<int, -450000, 450000, -225000> _diPhiStartAngle;
          NumericRange<int, -450000, 450000, 225000> _diPhiStopAngle;
        };

        ScanRange() = default;

        explicit ScanRange(NumericRange<int, 1, 1, 1> uiLength, std::array<aThetaAngleRangeItem, 1> aThetaAngleRange, std::array<aPhiAngleRangeItem, 1> aPhiAngleRange)
          : _uiLength(uiLength), _aThetaAngleRange(aThetaAngleRange), _aPhiAngleRange(aPhiAngleRange)
        {}

        NumericRange<int, 1, 1, 1> _uiLength;
        std::array<aThetaAngleRangeItem, 1> _aThetaAngleRange;
        std::array<aPhiAngleRangeItem, 1> _aPhiAngleRange;
      };

      Response() = default;

      explicit Response(NumericRange<int, 100, 2000, 2000> udiScanFreq, ScanRange ScanRange)
        : _udiScanFreq(udiScanFreq), _ScanRange(ScanRange)
      {}

      NumericRange<int, 100, 2000, 2000> _udiScanFreq;
      ScanRange _ScanRange;
    };

  }; // struct Get

}; // struct ScanConfig

} // namespace sick::multiScan200::v1_1_0::api::rest
