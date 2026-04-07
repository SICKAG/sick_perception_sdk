/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file certificateBundleInfo.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1_0R/certificateBundleInfo.g.hpp>
#include <nlohmann/json.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

inline void to_json(nlohmann::ordered_json& j, certificateBundleInfo::Get::Response::certificatesItem::namesItem const& obj)
{
  j = nlohmann::ordered_json{
      {"entry", obj._entry},
  };
}

inline void from_json(const nlohmann::json& j, certificateBundleInfo::Get::Response::certificatesItem::namesItem& obj)
{
  j.at("entry").get_to(obj._entry);
}

inline void to_json(nlohmann::ordered_json& j, certificateBundleInfo::Get::Response::certificatesItem const& obj)
{
  j = nlohmann::ordered_json{
      {"names", obj._names},
      {"issuer", obj._issuer},
      {"subject", obj._subject},
      {"serialNumber", obj._serialNumber},
      {"fingerprint", obj._fingerprint},
      {"validNotBefore", obj._validNotBefore},
      {"validNotAfter", obj._validNotAfter},
  };
}

inline void from_json(const nlohmann::json& j, certificateBundleInfo::Get::Response::certificatesItem& obj)
{
  j.at("names").get_to(obj._names);
  j.at("issuer").get_to(obj._issuer);
  j.at("subject").get_to(obj._subject);
  j.at("serialNumber").get_to(obj._serialNumber);
  j.at("fingerprint").get_to(obj._fingerprint);
  j.at("validNotBefore").get_to(obj._validNotBefore);
  j.at("validNotAfter").get_to(obj._validNotAfter);
}

inline void to_json(nlohmann::ordered_json& j, certificateBundleInfo::Get::Response::errorCode const& obj)
{
  j = nlohmann::ordered_json{
      {"error", obj._error},
  };
}

inline void from_json(const nlohmann::json& j, certificateBundleInfo::Get::Response::errorCode& obj)
{
  j.at("error").get_to(obj._error);
}

inline void to_json(nlohmann::ordered_json& j, certificateBundleInfo::Get::Response const& obj)
{
  j = nlohmann::ordered_json{
      {"uuidBundle", obj._uuidBundle},
      {"certificates", obj._certificates},
      {"errorCode", obj._errorCode},
  };
}

inline void from_json(const nlohmann::json& j, certificateBundleInfo::Get::Response& obj)
{
  j.at("uuidBundle").get_to(obj._uuidBundle);
  j.at("certificates").get_to(obj._certificates);
  j.at("errorCode").get_to(obj._errorCode);
}


} // namespace sick::picoScan120::v2_2_1_0R::api::rest
