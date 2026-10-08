/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file treatBlockedSectorsAsErrorSectors.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /treatBlockedSectorsAsErrorSectors.
*/
struct treatBlockedSectorsAsErrorSectors
{

  constexpr static const char* variableName = "treatBlockedSectorsAsErrorSectors";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the state if blocked sectors are treated as blocked or contaminated sectors.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool treatBlockedSectorsAsErrorSectors)
        : _treatBlockedSectorsAsErrorSectors(treatBlockedSectorsAsErrorSectors)
      {}

      bool _treatBlockedSectorsAsErrorSectors;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the state if blocked sectors are treated as blocked or contaminated sectors.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool treatBlockedSectorsAsErrorSectors)
        : _treatBlockedSectorsAsErrorSectors(treatBlockedSectorsAsErrorSectors)
      {}

      bool _treatBlockedSectorsAsErrorSectors;
    };

  }; // struct Post

}; // struct treatBlockedSectorsAsErrorSectors

} // namespace sick::multiScan200::v1_1_0::api::rest
