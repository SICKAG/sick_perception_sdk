/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetScanConfigList.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /SetScanConfigList.
*/
struct SetScanConfigList
{

  constexpr static const char* methodName = "SetScanConfigList";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the scan configuration profile (field of view, scanning frequency and angular resolution).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class ScanConfigList
      {
        Sc047h047v27620hz1x = 1,
        Sc047h094v27620hz1x = 2,
        Sc047h023v27620hz1x = 3,
        Sc047h047v36010hz1x = 4,
        Sc023h047v27620hz2x = 10,
        Sc023h023v27620hz2x = 11,
        Sc012h023v27620hz4x = 12,
        Sc047h047v19020hz1x = 20,
        Sc047h047v12020hz1x = 21,
      };

      Request() = default;

      explicit Request(ScanConfigList ScanConfigList)
        : _ScanConfigList(ScanConfigList)
      {}

      ScanConfigList _ScanConfigList;
    };

    struct Response
    {
      enum class eScanConfigError
      {
        SceOk = 0,
        SceErrorFreq = 1,
        SceErrorRes = 2,
        SceErrorFreqResComb = 3,
        SceErrorNumRange = 4,
        SceError = 5,
        SceErrorNoLicense = 6,
      };

      Response() = default;

      explicit Response(eScanConfigError eScanConfigError)
        : _eScanConfigError(eScanConfigError)
      {}

      eScanConfigError _eScanConfigError;
    };

  }; // struct Post

}; // struct SetScanConfigList

} // namespace sick::multiScan200::v1_1_0::api::rest
