/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationActiveSectors.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationActiveSectors.
*/
struct ContaminationActiveSectors
{

  constexpr static const char* variableName = "ContaminationActiveSectors";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the active contamination sectors. Starts with right backside of the sensor when looking to the device on topside view and continues counterclockwise.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<bool, 12> ContaminationActiveSectors)
        : _ContaminationActiveSectors(ContaminationActiveSectors)
      {}

      std::array<bool, 12> _ContaminationActiveSectors;
    };

  }; // struct Get

}; // struct ContaminationActiveSectors

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
