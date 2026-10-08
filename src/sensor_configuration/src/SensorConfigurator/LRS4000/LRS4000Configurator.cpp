/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Convert.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <memory>
#include <string>
#include <utility>

namespace sick::LRS4000::v1_10_0 {

Configurator::Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : Endpoints(std::move(httpClient), userLevel, std::move(password))
{ }

void Configurator::enableScanDataStreamingCompactTcp() const
{
  setScanDataFormat(api::rest::ScanDataFormat::Post::Request::ScanDataFormat::Compact);
}

auto Configurator::getSystemTimeOfSensor() const -> Timestamp
{
  return convert::toTimestamp(getDateTime());
}

} // namespace sick::LRS4000::v1_10_0
