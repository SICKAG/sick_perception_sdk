/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file setCertificateBundle.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_2_1/setCertificateBundle.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

inline void to_json(nlohmann::ordered_json& j, setCertificateBundle::Post::Request const& obj)
{
  j = nlohmann::ordered_json{
      {"contentCertificateBundle", obj._contentCertificateBundle},
      {"contentPrivateKey", obj._contentPrivateKey},
  };
}

inline void from_json(const nlohmann::json& j, setCertificateBundle::Post::Request& obj)
{
  j.at("contentCertificateBundle").get_to(obj._contentCertificateBundle);
  j.at("contentPrivateKey").get_to(obj._contentPrivateKey);
}


inline void to_json(nlohmann::ordered_json& j, setCertificateBundle::Post::Response::errorCode const& obj)
{
  j = nlohmann::ordered_json{
      {"error", obj._error},
  };
}

inline void from_json(const nlohmann::json& j, setCertificateBundle::Post::Response::errorCode& obj)
{
  j.at("error").get_to(obj._error);
}

inline void to_json(nlohmann::ordered_json& j, setCertificateBundle::Post::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"success", obj._success},
      {"errorCode", obj._errorCode},
  };
}

inline void from_json(const nlohmann::json& j, setCertificateBundle::Post::Response& obj)
{
  j.at("success").get_to(obj._success);
  j.at("errorCode").get_to(obj._errorCode);
}


} // namespace sick::picoScan150::v2_2_1::api::rest
