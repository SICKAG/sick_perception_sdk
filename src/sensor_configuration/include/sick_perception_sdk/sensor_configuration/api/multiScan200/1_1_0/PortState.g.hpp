/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PortState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

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

        explicit aInternalPortsItem(ePortState ePortState, int PortCounter)
          : _ePortState(ePortState), _PortCounter(PortCounter)
        {}

        ePortState _ePortState;
        int _PortCounter;
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

        explicit aExternalPortsItem(ePortState ePortState, int PortCounter)
          : _ePortState(ePortState), _PortCounter(PortCounter)
        {}

        ePortState _ePortState;
        int _PortCounter;
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

      explicit Response(int uiVersionNumber, int udiSystCount, std::vector<aInternalPortsItem> aInternalPorts, std::vector<aExternalPortsItem> aExternalPorts, std::vector<aTimeBlockItem> aTimeBlock)
        : _uiVersionNumber(uiVersionNumber), _udiSystCount(udiSystCount), _aInternalPorts(aInternalPorts), _aExternalPorts(aExternalPorts), _aTimeBlock(aTimeBlock)
      {}

      int _uiVersionNumber;
      int _udiSystCount;
      std::vector<aInternalPortsItem> _aInternalPorts;
      std::vector<aExternalPortsItem> _aExternalPorts;
      std::vector<aTimeBlockItem> _aTimeBlock;
    };

  }; // struct Get

}; // struct PortState

} // namespace sick::multiScan200::v1_1_0::api::rest
