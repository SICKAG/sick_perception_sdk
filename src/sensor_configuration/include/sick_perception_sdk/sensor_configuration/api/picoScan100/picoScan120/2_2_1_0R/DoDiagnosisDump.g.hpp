/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DoDiagnosisDump.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DoDiagnosisDump.
*/
struct DoDiagnosisDump
{

  constexpr static const char* methodName = "DoDiagnosisDump";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Creates a diagnostic file (zip file) for further analysis.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool DoRunlevelLoop, std::string Output)
        : _DoRunlevelLoop(DoRunlevelLoop), _Output(std::move(Output))
      {}

      bool _DoRunlevelLoop;
      std::string _Output;
    };

    struct Response
    {
      Response() = default;

      explicit Response(bool Successfull)
        : _Successfull(Successfull)
      {}

      bool _Successfull;
    };

  }; // struct Post

}; // struct DoDiagnosisDump

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
