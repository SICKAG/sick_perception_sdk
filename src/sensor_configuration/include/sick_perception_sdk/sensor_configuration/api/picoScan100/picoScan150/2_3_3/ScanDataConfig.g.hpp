/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataConfig.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ScanDataConfig.
*/
struct ScanDataConfig
{

  constexpr static const char* variableName = "ScanDataConfig";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the configuration of LMDscandata such as the content of the scan data (e.g. whether to include the RSSI values).
   */
  struct Get
  {
    struct Response
    {
      struct RemDataConfig
      {
        RemDataConfig() = default;

        explicit RemDataConfig(bool bEnable, std::uint8_t reserved1, std::uint8_t reserved2)
          : _bEnable(bEnable), _reserved1(reserved1), _reserved2(reserved2)
        {}

        bool _bEnable;
        std::uint8_t _reserved1;
        std::uint8_t _reserved2;
      };

      Response() = default;

      explicit Response(std::uint16_t reserved, RemDataConfig RemDataConfig, bool EnableEncoderBlock, bool reserved1, bool bEnableDeviceName, bool reserved2, bool bEnableTimeBlock, std::uint16_t reserved3)
        : _reserved(reserved), _RemDataConfig(RemDataConfig), _EnableEncoderBlock(EnableEncoderBlock), _reserved1(reserved1), _bEnableDeviceName(bEnableDeviceName), _reserved2(reserved2), _bEnableTimeBlock(bEnableTimeBlock), _reserved3(reserved3)
      {}

      std::uint16_t _reserved;
      RemDataConfig _RemDataConfig;
      bool _EnableEncoderBlock;
      bool _reserved1;
      bool _bEnableDeviceName;
      bool _reserved2;
      bool _bEnableTimeBlock;
      std::uint16_t _reserved3;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the configuration of LMDscandata such as the content of the scan data (e.g. whether to include the RSSI values).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      struct RemDataConfig
      {
        RemDataConfig() = default;

        explicit RemDataConfig(bool bEnable, std::uint8_t reserved1, std::uint8_t reserved2)
          : _bEnable(bEnable), _reserved1(reserved1), _reserved2(reserved2)
        {}

        bool _bEnable;
        std::uint8_t _reserved1;
        std::uint8_t _reserved2;
      };

      Request() = default;

      explicit Request(std::uint16_t reserved, RemDataConfig RemDataConfig, bool EnableEncoderBlock, bool reserved1, bool bEnableDeviceName, bool reserved2, bool bEnableTimeBlock, std::uint16_t reserved3)
        : _reserved(reserved), _RemDataConfig(RemDataConfig), _EnableEncoderBlock(EnableEncoderBlock), _reserved1(reserved1), _bEnableDeviceName(bEnableDeviceName), _reserved2(reserved2), _bEnableTimeBlock(bEnableTimeBlock), _reserved3(reserved3)
      {}

      std::uint16_t _reserved;
      RemDataConfig _RemDataConfig;
      bool _EnableEncoderBlock;
      bool _reserved1;
      bool _bEnableDeviceName;
      bool _reserved2;
      bool _bEnableTimeBlock;
      std::uint16_t _reserved3;
    };

  }; // struct Post

}; // struct ScanDataConfig

} // namespace sick::picoScan150::v2_3_3::api::rest
