/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActualEncPosition1Enable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /ActualEncPosition1Enable.
*/
struct ActualEncPosition1Enable
{

  constexpr static const char* variableName = "ActualEncPosition1Enable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the use of the 1st reference signal (port 3).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool ActualEncPosition1Enable)
        : _ActualEncPosition1Enable(ActualEncPosition1Enable)
      {}

      bool _ActualEncPosition1Enable;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the use of the 1st reference signal (port 3).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool ActualEncPosition1Enable)
        : _ActualEncPosition1Enable(ActualEncPosition1Enable)
      {}

      bool _ActualEncPosition1Enable;
    };

  }; // struct Post

}; // struct ActualEncPosition1Enable

} // namespace sick::picoScan150::v2_2_1::api::rest
