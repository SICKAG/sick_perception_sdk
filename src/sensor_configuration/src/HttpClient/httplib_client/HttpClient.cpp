/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClientBase.hpp>

#include <cstdint>
#include <string>

namespace sick::httplib_client {

HttpClient::HttpClient(IpV4Address address, std::uint16_t port)
  : HttpClientBase("http://" + address.toString() + ":" + std::to_string(port))
{ }

} // namespace sick::httplib_client
