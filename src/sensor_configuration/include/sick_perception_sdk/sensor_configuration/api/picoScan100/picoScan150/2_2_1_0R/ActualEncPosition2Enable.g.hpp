/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActualEncPosition2Enable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ActualEncPosition2Enable.
*/
struct ActualEncPosition2Enable
{

  constexpr static const char* variableName = "ActualEncPosition2Enable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the use of the 2nd reference signal (port 4).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool ActualEncPosition2Enable)
        : _ActualEncPosition2Enable(ActualEncPosition2Enable)
      {}

      bool _ActualEncPosition2Enable;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the use of the 2nd reference signal (port 4).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool ActualEncPosition2Enable)
        : _ActualEncPosition2Enable(ActualEncPosition2Enable)
      {}

      bool _ActualEncPosition2Enable;
    };

  }; // struct Post

}; // struct ActualEncPosition2Enable

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
