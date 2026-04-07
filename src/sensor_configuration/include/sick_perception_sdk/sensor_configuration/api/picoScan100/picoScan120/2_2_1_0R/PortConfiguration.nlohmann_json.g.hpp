/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PortConfiguration.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/PortConfiguration.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Get::Response::PortConfigurationItem::InputSettings const& obj)
{
  j = nlohmann::ordered_json{
      {"Logic", obj._Logic},
      {"Debounce", obj._Debounce.value()},
      {"Sensitivity", obj._Sensitivity},
      {"Reserved1", obj._Reserved1},
      {"Reserved2", obj._Reserved2},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Get::Response::PortConfigurationItem::InputSettings& obj)
{
  j.at("Logic").get_to(obj._Logic);
  j.at("Debounce").get_to(obj._Debounce);
  j.at("Sensitivity").get_to(obj._Sensitivity);
  j.at("Reserved1").get_to(obj._Reserved1);
  j.at("Reserved2").get_to(obj._Reserved2);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Get::Response::PortConfigurationItem::OutputSettings::SourcesItem const& obj)
{
  j = nlohmann::ordered_json{
      {"Name", obj._Name},
      {"Invert", obj._Invert},
      {"Reserved5", obj._Reserved5},
      {"Reserved6", obj._Reserved6},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Get::Response::PortConfigurationItem::OutputSettings::SourcesItem& obj)
{
  j.at("Name").get_to(obj._Name);
  j.at("Invert").get_to(obj._Invert);
  j.at("Reserved5").get_to(obj._Reserved5);
  j.at("Reserved6").get_to(obj._Reserved6);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Get::Response::PortConfigurationItem::OutputSettings const& obj)
{
  j = nlohmann::ordered_json{
      {"Logic", obj._Logic},
      {"OutputMode", obj._OutputMode},
      {"RestartType", obj._RestartType},
      {"RestartTime", obj._RestartTime.value()},
      {"RestartInput", obj._RestartInput.value()},
      {"Combination", obj._Combination},
      {"Reserved3", obj._Reserved3},
      {"Reserved4", obj._Reserved4},
      {"Sources", obj._Sources},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Get::Response::PortConfigurationItem::OutputSettings& obj)
{
  j.at("Logic").get_to(obj._Logic);
  j.at("OutputMode").get_to(obj._OutputMode);
  j.at("RestartType").get_to(obj._RestartType);
  j.at("RestartTime").get_to(obj._RestartTime);
  j.at("RestartInput").get_to(obj._RestartInput);
  j.at("Combination").get_to(obj._Combination);
  j.at("Reserved3").get_to(obj._Reserved3);
  j.at("Reserved4").get_to(obj._Reserved4);
  j.at("Sources").get_to(obj._Sources);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Get::Response::PortConfigurationItem const& obj)
{
  j = nlohmann::ordered_json{
      {"PortType", obj._PortType},
      {"Name", obj._Name},
      {"InputSettings", obj._InputSettings},
      {"OutputSettings", obj._OutputSettings},
      {"EncoderPortType", obj._EncoderPortType},
      {"Reserved8", obj._Reserved8},
      {"Reserved9", obj._Reserved9},
      {"Reserved10", obj._Reserved10},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Get::Response::PortConfigurationItem& obj)
{
  j.at("PortType").get_to(obj._PortType);
  j.at("Name").get_to(obj._Name);
  j.at("InputSettings").get_to(obj._InputSettings);
  j.at("OutputSettings").get_to(obj._OutputSettings);
  j.at("EncoderPortType").get_to(obj._EncoderPortType);
  j.at("Reserved8").get_to(obj._Reserved8);
  j.at("Reserved9").get_to(obj._Reserved9);
  j.at("Reserved10").get_to(obj._Reserved10);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Get::Response const& obj)
{
  j = obj._PortConfiguration;
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Get::Response& obj)
{
  j.get_to(obj._PortConfiguration);
}


inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Post::Request::PortConfigurationItem::InputSettings const& obj)
{
  j = nlohmann::ordered_json{
      {"Logic", obj._Logic},
      {"Debounce", obj._Debounce.value()},
      {"Sensitivity", obj._Sensitivity},
      {"Reserved1", obj._Reserved1},
      {"Reserved2", obj._Reserved2},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Post::Request::PortConfigurationItem::InputSettings& obj)
{
  j.at("Logic").get_to(obj._Logic);
  j.at("Debounce").get_to(obj._Debounce);
  j.at("Sensitivity").get_to(obj._Sensitivity);
  j.at("Reserved1").get_to(obj._Reserved1);
  j.at("Reserved2").get_to(obj._Reserved2);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Post::Request::PortConfigurationItem::OutputSettings::SourcesItem const& obj)
{
  j = nlohmann::ordered_json{
      {"Name", obj._Name},
      {"Invert", obj._Invert},
      {"Reserved5", obj._Reserved5},
      {"Reserved6", obj._Reserved6},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Post::Request::PortConfigurationItem::OutputSettings::SourcesItem& obj)
{
  j.at("Name").get_to(obj._Name);
  j.at("Invert").get_to(obj._Invert);
  j.at("Reserved5").get_to(obj._Reserved5);
  j.at("Reserved6").get_to(obj._Reserved6);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Post::Request::PortConfigurationItem::OutputSettings const& obj)
{
  j = nlohmann::ordered_json{
      {"Logic", obj._Logic},
      {"OutputMode", obj._OutputMode},
      {"RestartType", obj._RestartType},
      {"RestartTime", obj._RestartTime.value()},
      {"RestartInput", obj._RestartInput.value()},
      {"Combination", obj._Combination},
      {"Reserved3", obj._Reserved3},
      {"Reserved4", obj._Reserved4},
      {"Sources", obj._Sources},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Post::Request::PortConfigurationItem::OutputSettings& obj)
{
  j.at("Logic").get_to(obj._Logic);
  j.at("OutputMode").get_to(obj._OutputMode);
  j.at("RestartType").get_to(obj._RestartType);
  j.at("RestartTime").get_to(obj._RestartTime);
  j.at("RestartInput").get_to(obj._RestartInput);
  j.at("Combination").get_to(obj._Combination);
  j.at("Reserved3").get_to(obj._Reserved3);
  j.at("Reserved4").get_to(obj._Reserved4);
  j.at("Sources").get_to(obj._Sources);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Post::Request::PortConfigurationItem const& obj)
{
  j = nlohmann::ordered_json{
      {"PortType", obj._PortType},
      {"Name", obj._Name},
      {"InputSettings", obj._InputSettings},
      {"OutputSettings", obj._OutputSettings},
      {"EncoderPortType", obj._EncoderPortType},
      {"Reserved8", obj._Reserved8},
      {"Reserved9", obj._Reserved9},
      {"Reserved10", obj._Reserved10},
  };
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Post::Request::PortConfigurationItem& obj)
{
  j.at("PortType").get_to(obj._PortType);
  j.at("Name").get_to(obj._Name);
  j.at("InputSettings").get_to(obj._InputSettings);
  j.at("OutputSettings").get_to(obj._OutputSettings);
  j.at("EncoderPortType").get_to(obj._EncoderPortType);
  j.at("Reserved8").get_to(obj._Reserved8);
  j.at("Reserved9").get_to(obj._Reserved9);
  j.at("Reserved10").get_to(obj._Reserved10);
}

inline void to_json(nlohmann::ordered_json& j, PortConfiguration::Post::Request const& obj)
{
  j = obj._PortConfiguration;
}

inline void from_json(const nlohmann::json& j, PortConfiguration::Post::Request& obj)
{
  j.get_to(obj._PortConfiguration);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
