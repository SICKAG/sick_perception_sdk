/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFTchecksum.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /LFTchecksum.
*/
struct LFTchecksum
{

  constexpr static const char* variableName = "LFTchecksum";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns a checksum over all software parts and configurations.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool MD5SumOK, std::string MD5LinuxRoot, std::string MD5App, std::string MD5Calibration, std::string MD5Parameters)
        : _MD5SumOK(MD5SumOK), _MD5LinuxRoot(std::move(MD5LinuxRoot)), _MD5App(std::move(MD5App)), _MD5Calibration(std::move(MD5Calibration)), _MD5Parameters(std::move(MD5Parameters))
      {}

      bool _MD5SumOK;
      std::string _MD5LinuxRoot;
      std::string _MD5App;
      std::string _MD5Calibration;
      std::string _MD5Parameters;
    };

  }; // struct Get

}; // struct LFTchecksum

} // namespace sick::picoScan150::v2_2_1::api::rest
