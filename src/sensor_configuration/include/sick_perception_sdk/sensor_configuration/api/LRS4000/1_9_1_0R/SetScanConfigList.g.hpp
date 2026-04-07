/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetScanConfigList.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetScanConfigList.
*/
struct SetScanConfigList
{

  constexpr static const char* methodName = "SetScanConfigList";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Set a new device scan resolution/frequency combination. Please note that configurations, starting with value 3x or 9x switch the device from standard to extended range mode and values starting with x, 1x, 6x, 7x switch the device from extended range to normal mode.
   */
  struct Post
  {
    struct Request
    {
      enum class ScanConfigList
      {
        Invalid = 0,
        Sc125hz0020degM1801802overlap = 11,
        Sc125hz0020degM1801802il = 21,
        Sc125hz0040degM180180Noil = 1,
        Sc125hz0060degM180180Noil = 2,
        Sc125hz0100degM180180Noil = 4,
        Sc125hz0120degM180180Noil = 5,
        Sc250hz0040degM1801802overlap = 71,
        Sc250hz0040degM1801802il = 81,
        Sc250hz0080degM180180Noil = 61,
        Sc250hz0120degM180180Noil = 62,
        Sc250hz0200degM180180Noil = 64,
        Sc250hz0240degM180180Noil = 65,
        Sc125hz0240degM180180NoilXr = 31,
        Sc125hz0120degM1801802overlapXr = 32,
        Sc125hz0080degM1801803overlapXr = 33,
        Sc125hz0040degM1801803overlap2ilXr = 35,
        Sc250hz0480degM180180NoilXr = 91,
        Sc250hz0240degM1801802overlapXr = 92,
        Sc250hz0160degM1801803overlapXr = 93,
        Sc250hz0080degM1801803overlap2ilXr = 95,
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
      };

      Response() = default;

      explicit Response(eScanConfigError eScanConfigError)
        : _eScanConfigError(eScanConfigError)
      {}

      eScanConfigError _eScanConfigError;
    };

  }; // struct Post

}; // struct SetScanConfigList

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
