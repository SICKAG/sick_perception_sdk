/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LEDState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LEDState.
*/
struct LEDState
{

  constexpr static const char* variableName = "LEDState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the LED status.
   */
  struct Get
  {
    struct Response
    {
      struct LEDStateItem
      {
        enum class Color
        {
          Green = 0,
          Yellow = 1,
          Red = 2,
          White = 3,
        };

        enum class Function
        {
          On = 0,
          Off = 1,
          Blinking = 2,
          BlinkingFast = 3,
          BlinkingDelayed = 4,
          BlinkingColor = 5,
          BlinkingYellowRed = 6,
        };

        LEDStateItem() = default;

        explicit LEDStateItem(Color Color, Function Function, std::string Id)
          : _Color(Color), _Function(Function), _Id(std::move(Id))
        {}

        Color _Color;
        Function _Function;
        std::string _Id;
      };

      Response() = default;

      explicit Response(std::vector<LEDStateItem> LEDState)
        : _LEDState(LEDState)
      {}

      std::vector<LEDStateItem> _LEDState;
    };

  }; // struct Get

}; // struct LEDState

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
