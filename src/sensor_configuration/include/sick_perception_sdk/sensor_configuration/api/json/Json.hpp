/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// NOLINTBEGIN(readability-identifier-naming,readability-identifier-length): identifiers follow nlohmann::json naming conventions

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Challenge.hpp>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <sick_perception_sdk/sensor_configuration/api/SrtRest.hpp>

#include <nlohmann/json.hpp>
#include <string>

namespace sick {

// Define serialization functions of public types before the detail namespace
// so they can be used by data types in the detail namespace.

// IpV4Address
inline void to_json(nlohmann::ordered_json& j, IpV4Address const& addr)
{
  auto const& bytes = addr.bytes();
  j                 = nlohmann::ordered_json::array({bytes[0], bytes[1], bytes[2], bytes[3]});
}

// ResponseHeader
inline void from_json(nlohmann::json const& j, ResponseHeader& h)
{
  j.at("status").get_to(h.status);
  j.at("message").get_to(h.message);
}

// Challenge
inline void from_json(nlohmann::json const& j, Challenge& c)
{
  j.at("realm").get_to(c.realm);
  j.at("nonce").get_to(c.nonce);
  j.at("opaque").get_to(c.opaque);
  j.at("salt").get_to(c.salt);
}

// AuthenticationHeader
inline void to_json(nlohmann::ordered_json& j, AuthenticationHeader const& a)
{
  j = nlohmann::ordered_json {{"nonce", a.nonce}, {"opaque", a.opaque}, {"realm", a.realm}, {"response", a.response}, {"user", a.user}};
}

namespace json {

template <class ValueT>
auto deserialize(std::string const& json, std::string const& fieldName, bool withDataField = true) -> ValueT
{
  nlohmann::json jsonObj = nlohmann::json::parse(json);
  if (withDataField)
  {
    return jsonObj.at("data").at(fieldName).template get<ValueT>();
  }
  return jsonObj.at(fieldName).template get<ValueT>();
}

} // namespace json

} // namespace sick

// NOLINTEND(readability-identifier-naming,readability-identifier-length)
