/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file rosFrameId.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /rosFrameId.
*/
struct rosFrameId
{

  constexpr static const char* variableName = "rosFrameId";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the frame ID of the published topics.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string rosFrameId)
        : _rosFrameId(std::move(rosFrameId))
      {}

      std::string _rosFrameId;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the frame ID of the published topics.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string rosFrameId)
        : _rosFrameId(std::move(rosFrameId))
      {}

      std::string _rosFrameId;
    };

  }; // struct Post

}; // struct rosFrameId

} // namespace sick::multiScan200::v1_1_0::api::rest
