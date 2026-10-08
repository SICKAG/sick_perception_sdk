/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/Endpoints.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace sick::LRS4000::v1_10_0 {

/**
 * @brief Configurator for LRS4000 sensors.
 * 
 * @ingroup sensor_configuration
 */
class SDK_EXPORT Configurator : public Endpoints
{
public:
  explicit Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);
  ~Configurator() = default;

  Configurator(Configurator const&)                    = delete;
  auto operator=(Configurator const&) -> Configurator& = delete;
  Configurator(Configurator&&)                         = default;
  auto operator=(Configurator&&) -> Configurator&      = default;

  void enableScanDataStreamingCompactTcp() const;
  auto getSystemTimeOfSensor() const -> Timestamp;
};

} // namespace sick::LRS4000::v1_10_0
