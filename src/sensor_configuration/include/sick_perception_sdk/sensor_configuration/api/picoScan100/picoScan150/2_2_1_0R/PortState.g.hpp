/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PortState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /PortState.
*/
struct PortState
{

  constexpr static const char* variableName = "PortState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the state of the ports. "PortState" is preferred over "OutputState".
   */
  struct Get
  {
    struct Response
    {
      struct aInternalPortsItem
      {
        enum class ePortState
        {
          OutputNotActive = 0,
          OutputActive = 1,
          Tristate = 2,
          InputActive = 3,
          InputNotActive = 4,
        };

        aInternalPortsItem() = default;

        explicit aInternalPortsItem(ePortState ePortState, std::uint32_t PortCounter)
          : _ePortState(ePortState), _PortCounter(PortCounter)
        {}

        ePortState _ePortState;
        std::uint32_t _PortCounter;
      };

      struct aExternalPortsItem
      {
        enum class ePortState
        {
          OutputNotActive = 0,
          OutputActive = 1,
          Tristate = 2,
          InputActive = 3,
          InputNotActive = 4,
        };

        aExternalPortsItem() = default;

        explicit aExternalPortsItem(ePortState ePortState, std::uint32_t PortCounter)
          : _ePortState(ePortState), _PortCounter(PortCounter)
        {}

        ePortState _ePortState;
        std::uint32_t _PortCounter;
      };

      struct aTimeBlockItem
      {
        aTimeBlockItem() = default;

        explicit aTimeBlockItem(NumericRange<std::uint16_t, 0, 2105, 0> uiYear, NumericRange<std::uint8_t, 0, 12, 1> usiMonth, NumericRange<std::uint8_t, 0, 31, 1> usiDay, NumericRange<std::uint8_t, 0, 23, 0> usiHour, NumericRange<std::uint8_t, 0, 59, 0> usiMinute, NumericRange<std::uint8_t, 0, 59, 0> usiSec, NumericRange<std::uint32_t, 0, 999999, 0> udiUSec)
          : _uiYear(std::move(uiYear)), _usiMonth(std::move(usiMonth)), _usiDay(std::move(usiDay)), _usiHour(std::move(usiHour)), _usiMinute(std::move(usiMinute)), _usiSec(std::move(usiSec)), _udiUSec(std::move(udiUSec))
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

      explicit Response(std::uint16_t uiVersionNumber, std::uint32_t udiSystCount, std::vector<aInternalPortsItem> aInternalPorts, std::vector<aExternalPortsItem> aExternalPorts, std::vector<aTimeBlockItem> aTimeBlock)
        : _uiVersionNumber(uiVersionNumber), _udiSystCount(udiSystCount), _aInternalPorts(aInternalPorts), _aExternalPorts(aExternalPorts), _aTimeBlock(aTimeBlock)
      {}

      std::uint16_t _uiVersionNumber;
      std::uint32_t _udiSystCount;
      std::vector<aInternalPortsItem> _aInternalPorts;
      std::vector<aExternalPortsItem> _aExternalPorts;
      std::vector<aTimeBlockItem> _aTimeBlock;
    };

  }; // struct Get

}; // struct PortState

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
