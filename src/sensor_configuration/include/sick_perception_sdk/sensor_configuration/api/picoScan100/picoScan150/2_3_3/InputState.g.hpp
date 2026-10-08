/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InputState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <vector>

namespace sick::picoScan150::v2_3_3::api::rest {

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

        explicit aTimeBlockItem(NumericRange<std::uint16_t, 0, 2105, 0> uiYear, NumericRange<std::uint8_t, 0, 12, 1> usiMonth, NumericRange<std::uint8_t, 0, 31, 1> usiDay, NumericRange<std::uint8_t, 0, 23, 0> usiHour, NumericRange<std::uint8_t, 0, 59, 0> usiMinute, NumericRange<std::uint8_t, 0, 59, 0> usiSec, NumericRange<std::uint32_t, 0, 999999, 0> udiUSec)
          : _uiYear(uiYear), _usiMonth(usiMonth), _usiDay(usiDay), _usiHour(usiHour), _usiMinute(usiMinute), _usiSec(usiSec), _udiUSec(udiUSec)
        {}

        NumericRange<std::uint16_t, 0, 2105, 0> _uiYear;
        NumericRange<std::uint8_t, 0, 12, 1> _usiMonth;
        NumericRange<std::uint8_t, 0, 31, 1> _usiDay;
        NumericRange<std::uint8_t, 0, 23, 0> _usiHour;
        NumericRange<std::uint8_t, 0, 59, 0> _usiMinute;
        NumericRange<std::uint8_t, 0, 59, 0> _usiSec;
        NumericRange<std::uint32_t, 0, 999999, 0> _udiUSec;
      };

      Response() = default;

      explicit Response(std::uint16_t uiVersionNumber, std::uint32_t udiSystCount, std::array<aDigitalInItem, 8> aDigitalIn, std::vector<aTimeBlockItem> aTimeBlock)
        : _uiVersionNumber(uiVersionNumber), _udiSystCount(udiSystCount), _aDigitalIn(aDigitalIn), _aTimeBlock(aTimeBlock)
      {}

      std::uint16_t _uiVersionNumber;
      std::uint32_t _udiSystCount;
      std::array<aDigitalInItem, 8> _aDigitalIn;
      std::vector<aTimeBlockItem> _aTimeBlock;
    };

  }; // struct Get

}; // struct InputState

} // namespace sick::picoScan150::v2_3_3::api::rest
