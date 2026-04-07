/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherColaTransmitTimeout.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherColaTransmitTimeout.
*/
struct EtherColaTransmitTimeout
{

  constexpr static const char* methodName = "EtherColaTransmitTimeout";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief This parameter should only be changed in case the sensor is connected to a network where reconnections may be required caused by e.g. loose contact of the Ethernet cable. This command changes the Acknowledge timeout for TCP based CoLa protocols. Reducing the Acknowledge timeout allows a faster restart of data transmission after unwanted disconnects. In large networks with high amount of data traffic, a reduced Acknowledge timeout may lead to a port close, initiated by the sensor.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::uint16_t, 250, 15000, 15000> EtherColaTransmitTimeout)
        : _EtherColaTransmitTimeout(std::move(EtherColaTransmitTimeout))
      {}

      NumericRange<std::uint16_t, 250, 15000, 15000> _EtherColaTransmitTimeout;
    };

  }; // struct Post

}; // struct EtherColaTransmitTimeout

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
