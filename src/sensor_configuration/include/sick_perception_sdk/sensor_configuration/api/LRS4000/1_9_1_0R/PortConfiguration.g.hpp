/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PortConfiguration.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <string>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /PortConfiguration.
*/
struct PortConfiguration
{

  constexpr static const char* variableName = "PortConfiguration";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the port configuration of all I/Os.
   */
  struct Get
  {
    struct Response
    {
      struct PortConfigurationItem
      {
        enum class PortType
        {
          Input = 0,
          Output = 1,
        };

        struct InputSettings
        {
          enum class Logic
          {
            ActiveHigh = 0,
            ActiveLow = 1,
          };

          enum class Sensitivity
          {
            Edge = 0,
            Level = 1,
          };

          InputSettings() = default;

          explicit InputSettings(Logic Logic, NumericRange<std::uint16_t, 5, 10000, 10> Debounce, Sensitivity Sensitivity, std::uint16_t Reserved1, std::uint16_t Reserved2)
            : _Logic(Logic), _Debounce(std::move(Debounce)), _Sensitivity(Sensitivity), _Reserved1(Reserved1), _Reserved2(Reserved2)
          {}

          Logic _Logic;
          NumericRange<std::uint16_t, 5, 10000, 10> _Debounce;
          Sensitivity _Sensitivity;
          std::uint16_t _Reserved1;
          std::uint16_t _Reserved2;
        };

        struct OutputSettings
        {
          enum class Logic
          {
            ActiveHigh = 0,
            ActiveLow = 1,
          };

          enum class OutputMode
          {
            Pnp = 0,
            Npn = 1,
            PushPull = 2,
          };

          enum class RestartType
          {
            RestartImmedate = 0,
            RestartTime = 1,
            RestartInput = 2,
          };

          enum class Combination
          {
            And = 0,
            Or = 1,
            Xor = 2,
          };

          struct SourcesItem
          {
            SourcesItem() = default;

            explicit SourcesItem(std::string Name, bool Invert, std::uint8_t Reserved5, std::uint8_t Reserved6)
              : _Name(std::move(Name)), _Invert(Invert), _Reserved5(Reserved5), _Reserved6(Reserved6)
            {}

            std::string _Name;
            bool _Invert;
            std::uint8_t _Reserved5;
            std::uint8_t _Reserved6;
          };

          OutputSettings() = default;

          explicit OutputSettings(Logic Logic, OutputMode OutputMode, RestartType RestartType, NumericRange<std::uint32_t, 20, 600000, 200> RestartTime, NumericRange<std::uint16_t, 1, 8, 1> RestartInput, Combination Combination, std::uint16_t Reserved3, std::uint16_t Reserved4, std::vector<SourcesItem> Sources)
            : _Logic(Logic), _OutputMode(OutputMode), _RestartType(RestartType), _RestartTime(std::move(RestartTime)), _RestartInput(std::move(RestartInput)), _Combination(Combination), _Reserved3(Reserved3), _Reserved4(Reserved4), _Sources(Sources)
          {}

          Logic _Logic;
          OutputMode _OutputMode;
          RestartType _RestartType;
          NumericRange<std::uint32_t, 20, 600000, 200> _RestartTime;
          NumericRange<std::uint16_t, 1, 8, 1> _RestartInput;
          Combination _Combination;
          std::uint16_t _Reserved3;
          std::uint16_t _Reserved4;
          std::vector<SourcesItem> _Sources;
        };

        PortConfigurationItem() = default;

        explicit PortConfigurationItem(PortType PortType, std::string Name, InputSettings InputSettings, OutputSettings OutputSettings, std::uint16_t Reserved7, std::uint16_t Reserved8, std::uint16_t Reserved9, std::uint16_t Reserved10)
          : _PortType(PortType), _Name(std::move(Name)), _InputSettings(InputSettings), _OutputSettings(OutputSettings), _Reserved7(Reserved7), _Reserved8(Reserved8), _Reserved9(Reserved9), _Reserved10(Reserved10)
        {}

        PortType _PortType;
        std::string _Name;
        InputSettings _InputSettings;
        OutputSettings _OutputSettings;
        std::uint16_t _Reserved7;
        std::uint16_t _Reserved8;
        std::uint16_t _Reserved9;
        std::uint16_t _Reserved10;
      };

      Response() = default;

      explicit Response(std::array<PortConfigurationItem, 6> PortConfiguration)
        : _PortConfiguration(PortConfiguration)
      {}

      std::array<PortConfigurationItem, 6> _PortConfiguration;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the port configuration of all I/Os.
   */
  struct Post
  {
    struct Request
    {
      struct PortConfigurationItem
      {
        enum class PortType
        {
          Input = 0,
          Output = 1,
        };

        struct InputSettings
        {
          enum class Logic
          {
            ActiveHigh = 0,
            ActiveLow = 1,
          };

          enum class Sensitivity
          {
            Edge = 0,
            Level = 1,
          };

          InputSettings() = default;

          explicit InputSettings(Logic Logic, NumericRange<std::uint16_t, 5, 10000, 10> Debounce, Sensitivity Sensitivity, std::uint16_t Reserved1, std::uint16_t Reserved2)
            : _Logic(Logic), _Debounce(std::move(Debounce)), _Sensitivity(Sensitivity), _Reserved1(Reserved1), _Reserved2(Reserved2)
          {}

          Logic _Logic;
          NumericRange<std::uint16_t, 5, 10000, 10> _Debounce;
          Sensitivity _Sensitivity;
          std::uint16_t _Reserved1;
          std::uint16_t _Reserved2;
        };

        struct OutputSettings
        {
          enum class Logic
          {
            ActiveHigh = 0,
            ActiveLow = 1,
          };

          enum class OutputMode
          {
            Pnp = 0,
            Npn = 1,
            PushPull = 2,
          };

          enum class RestartType
          {
            RestartImmedate = 0,
            RestartTime = 1,
            RestartInput = 2,
          };

          enum class Combination
          {
            And = 0,
            Or = 1,
            Xor = 2,
          };

          struct SourcesItem
          {
            SourcesItem() = default;

            explicit SourcesItem(std::string Name, bool Invert, std::uint8_t Reserved5, std::uint8_t Reserved6)
              : _Name(std::move(Name)), _Invert(Invert), _Reserved5(Reserved5), _Reserved6(Reserved6)
            {}

            std::string _Name;
            bool _Invert;
            std::uint8_t _Reserved5;
            std::uint8_t _Reserved6;
          };

          OutputSettings() = default;

          explicit OutputSettings(Logic Logic, OutputMode OutputMode, RestartType RestartType, NumericRange<std::uint32_t, 20, 600000, 200> RestartTime, NumericRange<std::uint16_t, 1, 8, 1> RestartInput, Combination Combination, std::uint16_t Reserved3, std::uint16_t Reserved4, std::vector<SourcesItem> Sources)
            : _Logic(Logic), _OutputMode(OutputMode), _RestartType(RestartType), _RestartTime(std::move(RestartTime)), _RestartInput(std::move(RestartInput)), _Combination(Combination), _Reserved3(Reserved3), _Reserved4(Reserved4), _Sources(Sources)
          {}

          Logic _Logic;
          OutputMode _OutputMode;
          RestartType _RestartType;
          NumericRange<std::uint32_t, 20, 600000, 200> _RestartTime;
          NumericRange<std::uint16_t, 1, 8, 1> _RestartInput;
          Combination _Combination;
          std::uint16_t _Reserved3;
          std::uint16_t _Reserved4;
          std::vector<SourcesItem> _Sources;
        };

        PortConfigurationItem() = default;

        explicit PortConfigurationItem(PortType PortType, std::string Name, InputSettings InputSettings, OutputSettings OutputSettings, std::uint16_t Reserved7, std::uint16_t Reserved8, std::uint16_t Reserved9, std::uint16_t Reserved10)
          : _PortType(PortType), _Name(std::move(Name)), _InputSettings(InputSettings), _OutputSettings(OutputSettings), _Reserved7(Reserved7), _Reserved8(Reserved8), _Reserved9(Reserved9), _Reserved10(Reserved10)
        {}

        PortType _PortType;
        std::string _Name;
        InputSettings _InputSettings;
        OutputSettings _OutputSettings;
        std::uint16_t _Reserved7;
        std::uint16_t _Reserved8;
        std::uint16_t _Reserved9;
        std::uint16_t _Reserved10;
      };

      Request() = default;

      explicit Request(std::array<PortConfigurationItem, 6> PortConfiguration)
        : _PortConfiguration(PortConfiguration)
      {}

      std::array<PortConfigurationItem, 6> _PortConfiguration;
    };

  }; // struct Post

}; // struct PortConfiguration

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
