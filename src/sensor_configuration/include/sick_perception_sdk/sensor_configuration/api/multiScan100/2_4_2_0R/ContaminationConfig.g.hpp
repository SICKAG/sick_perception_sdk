/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationConfig.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationConfig.
*/
struct ContaminationConfig
{

  constexpr static const char* variableName = "ContaminationConfig";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets of the contamination indication settings such as sensitivity, response time, threshold for warning, and active sectors.
   */
  struct Get
  {
    struct Response
    {
      enum class eStrategy
      {
        CmStrategyInactive = 0,
        CmStrategyHighAvailable = 1,
        CmStrategySensitive = 2,
      };

      enum class eThreshold
      {
        CmLow = 0,
        CmMid = 1,
        CmHigh = 2,
      };

      enum class eCover
      {
        CmCoverNone = 0,
        CmCover = 6,
        CmCoverCustomSectors = 255,
      };

      Response() = default;

      explicit Response(eStrategy eStrategy, NumericRange<std::uint16_t, 3, 60, 3> usiResponseTime, eThreshold eThreshold, eCover eCover, std::vector<bool> CustomSectors, bool bEnableWarning, bool bEnableError)
        : _eStrategy(eStrategy), _usiResponseTime(std::move(usiResponseTime)), _eThreshold(eThreshold), _eCover(eCover), _CustomSectors(CustomSectors), _bEnableWarning(bEnableWarning), _bEnableError(bEnableError)
      {}

      eStrategy _eStrategy;
      NumericRange<std::uint16_t, 3, 60, 3> _usiResponseTime;
      eThreshold _eThreshold;
      eCover _eCover;
      std::vector<bool> _CustomSectors;
      bool _bEnableWarning;
      bool _bEnableError;
    };

  }; // struct Get

  /**
   * @brief Returns/sets of the contamination indication settings such as sensitivity, response time, threshold for warning, and active sectors.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class eStrategy
      {
        CmStrategyInactive = 0,
        CmStrategyHighAvailable = 1,
        CmStrategySensitive = 2,
      };

      enum class eThreshold
      {
        CmLow = 0,
        CmMid = 1,
        CmHigh = 2,
      };

      enum class eCover
      {
        CmCoverNone = 0,
        CmCover = 6,
        CmCoverCustomSectors = 255,
      };

      Request() = default;

      explicit Request(eStrategy eStrategy, NumericRange<std::uint16_t, 3, 60, 3> usiResponseTime, eThreshold eThreshold, eCover eCover, std::vector<bool> CustomSectors, bool bEnableWarning, bool bEnableError)
        : _eStrategy(eStrategy), _usiResponseTime(std::move(usiResponseTime)), _eThreshold(eThreshold), _eCover(eCover), _CustomSectors(CustomSectors), _bEnableWarning(bEnableWarning), _bEnableError(bEnableError)
      {}

      eStrategy _eStrategy;
      NumericRange<std::uint16_t, 3, 60, 3> _usiResponseTime;
      eThreshold _eThreshold;
      eCover _eCover;
      std::vector<bool> _CustomSectors;
      bool _bEnableWarning;
      bool _bEnableError;
    };

  }; // struct Post

}; // struct ContaminationConfig

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
