/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file enableCloningPlug.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /enableCloningPlug.
*/
struct enableCloningPlug
{

  constexpr static const char* variableName = "enableCloningPlug";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the cloning functionality of the system plug.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool enableCloningPlug)
        : _enableCloningPlug(enableCloningPlug)
      {}

      bool _enableCloningPlug;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the cloning functionality of the system plug.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool enableCloningPlug)
        : _enableCloningPlug(enableCloningPlug)
      {}

      bool _enableCloningPlug;
    };

  }; // struct Post

}; // struct enableCloningPlug

} // namespace sick::picoScan150::v2_3_3::api::rest
