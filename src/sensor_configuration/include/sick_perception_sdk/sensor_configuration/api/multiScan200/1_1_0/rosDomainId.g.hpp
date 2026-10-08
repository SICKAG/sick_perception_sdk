/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file rosDomainId.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /rosDomainId.
*/
struct rosDomainId
{

  constexpr static const char* variableName = "rosDomainId";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the ros domain ID.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(int rosDomainId)
        : _rosDomainId(rosDomainId)
      {}

      int _rosDomainId;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the ros domain ID.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(int rosDomainId)
        : _rosDomainId(rosDomainId)
      {}

      int _rosDomainId;
    };

  }; // struct Post

}; // struct rosDomainId

} // namespace sick::multiScan200::v1_1_0::api::rest
