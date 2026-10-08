/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/json/Json.hpp>

#include <nlohmann/json.hpp>
#include <string>

namespace sick {

/**
 * @file SopasClientImpl.hpp
 * 
 * @brief Out-of-line definitions of the `SopasClient` typed template primitives.
 *
 * This header intentionally pulls in `nlohmann/json`. It must be included **only** by the generated
 * `Endpoints.g.cpp` files (which also include the endpoint serializers), never by consumer code, so
 * that `nlohmann/json` stays private to the SDK library build.
 * 
 * @ingroup sensor_configuration
 */

template <class EndpointT>
auto SopasClient::readVariable() const -> typename EndpointT::Get::Response
{
  static_assert(!EndpointT::isSopasMethod, "EndpointT is a SOPAS method; use invokeMethod().");
  auto const json = nlohmann::json::parse(sendJsonGet(std::string("/api/") + EndpointT::variableName));
  return json.at("data").at(EndpointT::variableName).template get<typename EndpointT::Get::Response>();
}

template <class EndpointT>
void SopasClient::writeVariable(typename EndpointT::Post::Request const& payload) const
{
  static_assert(!EndpointT::isSopasMethod, "EndpointT is a SOPAS method; use invokeMethod().");
  nlohmann::ordered_json body;
  body["header"]                        = authenticate(EndpointT::variableName);
  body["data"][EndpointT::variableName] = payload;
  sendJsonPost(std::string("/api/") + EndpointT::variableName, body.dump());
}

template <class EndpointT>
auto SopasClient::invokeMethod(typename EndpointT::Post::Request const& payload) const -> typename EndpointT::Post::Response
{
  static_assert(EndpointT::isSopasMethod, "EndpointT is a SOPAS variable; use writeVariable().");
  nlohmann::ordered_json body;
  body["header"]  = authenticate(EndpointT::methodName);
  body["data"]    = payload;
  auto const json = nlohmann::json::parse(sendJsonPost(std::string("/api/") + EndpointT::methodName, body.dump()));
  return json.at("data").template get<typename EndpointT::Post::Response>();
}

template <class EndpointT>
void SopasClient::invokeMethodWithoutResponse(typename EndpointT::Post::Request const& payload) const
{
  static_assert(EndpointT::isSopasMethod, "EndpointT is a SOPAS variable; use writeVariable().");
  nlohmann::ordered_json body;
  body["header"] = authenticate(EndpointT::methodName);
  body["data"]   = payload;
  sendJsonPost(std::string("/api/") + EndpointT::methodName, body.dump());
}

template <class EndpointT>
auto SopasClient::invokeMethodWithoutRequest() const -> typename EndpointT::Post::Response
{
  static_assert(EndpointT::isSopasMethod, "EndpointT is a SOPAS variable; use writeVariable().");
  nlohmann::ordered_json body;
  body["header"]  = authenticate(EndpointT::methodName);
  auto const json = nlohmann::json::parse(sendJsonPost(std::string("/api/") + EndpointT::methodName, body.dump()));
  return json.at("data").template get<typename EndpointT::Post::Response>();
}

template <class EndpointT>
void SopasClient::invokeMethodWithoutRequestAndResponse() const
{
  static_assert(EndpointT::isSopasMethod, "EndpointT is a SOPAS variable; use writeVariable().");
  nlohmann::ordered_json body;
  body["header"] = authenticate(EndpointT::methodName);
  sendJsonPost(std::string("/api/") + EndpointT::methodName, body.dump());
}

} // namespace sick
