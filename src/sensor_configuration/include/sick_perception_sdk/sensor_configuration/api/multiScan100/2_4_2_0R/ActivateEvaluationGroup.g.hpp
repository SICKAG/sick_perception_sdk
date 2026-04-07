/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ActivateEvaluationGroup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /ActivateEvaluationGroup.
*/
struct ActivateEvaluationGroup
{

  constexpr static const char* methodName = "ActivateEvaluationGroup";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the activation condition for all existing evaluation groups (not configured, active, or inactive).
   */
  struct Post
  {
    struct Request
    {
      struct ListItem
      {
        ListItem() = default;

        explicit ListItem(NumericRange<std::uint16_t, 1, 48, 1> GroupId, bool Activate)
          : _GroupId(std::move(GroupId)), _Activate(Activate)
        {}

        NumericRange<std::uint16_t, 1, 48, 1> _GroupId;
        bool _Activate;
      };

      Request() = default;

      explicit Request(std::vector<ListItem> List)
        : _List(List)
      {}

      std::vector<ListItem> _List;
    };

    struct Response
    {
      Response() = default;

      explicit Response(std::vector<bool> Success)
        : _Success(Success)
      {}

      std::vector<bool> _Success;
    };

  }; // struct Post

}; // struct ActivateEvaluationGroup

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
