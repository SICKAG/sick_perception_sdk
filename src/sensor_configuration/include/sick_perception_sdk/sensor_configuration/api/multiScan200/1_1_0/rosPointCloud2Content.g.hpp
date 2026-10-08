/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file rosPointCloud2Content.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /rosPointCloud2Content.
*/
struct rosPointCloud2Content
{

  constexpr static const char* variableName = "rosPointCloud2Content";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the content of the published PointCloud2 topics.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool includeRssi, bool includeProperties, bool includeTimeOffset, bool includeRing)
        : _includeRssi(includeRssi), _includeProperties(includeProperties), _includeTimeOffset(includeTimeOffset), _includeRing(includeRing)
      {}

      bool _includeRssi;
      bool _includeProperties;
      bool _includeTimeOffset;
      bool _includeRing;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the content of the published PointCloud2 topics.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool includeRssi, bool includeProperties, bool includeTimeOffset, bool includeRing)
        : _includeRssi(includeRssi), _includeProperties(includeProperties), _includeTimeOffset(includeTimeOffset), _includeRing(includeRing)
      {}

      bool _includeRssi;
      bool _includeProperties;
      bool _includeTimeOffset;
      bool _includeRing;
    };

  }; // struct Post

}; // struct rosPointCloud2Content

} // namespace sick::multiScan200::v1_1_0::api::rest
