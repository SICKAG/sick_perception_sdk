/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file bloomingFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /bloomingFilter.
*/
struct bloomingFilter
{

  constexpr static const char* variableName = "bloomingFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the blooming filter.
   */
  struct Get
  {
    struct Response
    {
      enum class strength
      {
        Low = 0,
        Medium = 1,
        Strong = 2,
      };

      Response() = default;

      explicit Response(strength strength, bool enable)
        : _strength(strength), _enable(enable)
      {}

      strength _strength;
      bool _enable;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the blooming filter.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class strength
      {
        Low = 0,
        Medium = 1,
        Strong = 2,
      };

      Request() = default;

      explicit Request(strength strength, bool enable)
        : _strength(strength), _enable(enable)
      {}

      strength _strength;
      bool _enable;
    };

  }; // struct Post

}; // struct bloomingFilter

} // namespace sick::multiScan200::v1_1_0::api::rest
