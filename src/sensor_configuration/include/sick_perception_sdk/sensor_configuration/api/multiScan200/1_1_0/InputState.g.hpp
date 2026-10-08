/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InputState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /InputState.
*/
struct InputState
{

  constexpr static const char* variableName = "InputState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the state of all inputs.
   */
  struct Get
  {
    struct Response
    {
      struct aDigitalInItem
      {
        struct IOState
        {
          enum class eIOState
          {
            IosLow = 0,
            IosHigh = 1,
            IosTristate = 2,
          };

          IOState() = default;

          explicit IOState(eIOState eIOState)
            : _eIOState(eIOState)
          {}

          eIOState _eIOState;
        };

        aDigitalInItem() = default;

        explicit aDigitalInItem(IOState IOState)
          : _IOState(IOState)
        {}

        IOState _IOState;
      };

      struct aTimeBlockItem
      {
        aTimeBlockItem() = default;

        explicit aTimeBlockItem(NumericRange<int, 0, 2105, 0> uiYear, NumericRange<int, 0, 12, 1> usiMonth, NumericRange<int, 0, 31, 1> usiDay, NumericRange<int, 0, 23, 0> usiHour, NumericRange<int, 0, 59, 0> usiMinute, NumericRange<int, 0, 59, 0> usiSec, NumericRange<int, 0, 999999, 0> udiUSec)
          : _uiYear(uiYear), _usiMonth(usiMonth), _usiDay(usiDay), _usiHour(usiHour), _usiMinute(usiMinute), _usiSec(usiSec), _udiUSec(udiUSec)
        {}

        NumericRange<int, 0, 2105, 0> _uiYear;
        NumericRange<int, 0, 12, 1> _usiMonth;
        NumericRange<int, 0, 31, 1> _usiDay;
        NumericRange<int, 0, 23, 0> _usiHour;
        NumericRange<int, 0, 59, 0> _usiMinute;
        NumericRange<int, 0, 59, 0> _usiSec;
        NumericRange<int, 0, 999999, 0> _udiUSec;
      };

      Response() = default;

      explicit Response(int uiVersionNumber, int udiSystCount, std::array<aDigitalInItem, 8> aDigitalIn, std::vector<aTimeBlockItem> aTimeBlock)
        : _uiVersionNumber(uiVersionNumber), _udiSystCount(udiSystCount), _aDigitalIn(aDigitalIn), _aTimeBlock(aTimeBlock)
      {}

      int _uiVersionNumber;
      int _udiSystCount;
      std::array<aDigitalInItem, 8> _aDigitalIn;
      std::vector<aTimeBlockItem> _aTimeBlock;
    };

  }; // struct Get

}; // struct InputState

} // namespace sick::multiScan200::v1_1_0::api::rest
