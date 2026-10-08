/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/Endpoints.g.hpp>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace sick::multiScan100::v2_4_4 {

constexpr auto DefaultTimeout = Duration::fromSeconds(10);

/**
 * @brief Configurator for multiScan100 sensors.
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

  void enableImuStreamingCompactUdp(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
  void enableScanDataStreamingCompactUdp(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
  auto getSystemTimeOfSensor() const -> Timestamp;

  auto backupParameters(std::string const& passphrase, Duration timeout = DefaultTimeout) const -> std::string;
  void restoreParameters(std::string const& backupContent, std::string const& passphrase, Duration timeout = DefaultTimeout) const;

  /**
   * @brief Upload and apply a firmware image to the sensor.
   *
   * @param timeout When set, the call blocks and polls the update status until the update finishes,
   * fails, or the timeout elapses. When left empty (std::nullopt) the update is only triggered and
   * the call returns immediately without waiting for completion.
   */
  void updateFirmware(std::string const& firmwareFilePath, std::optional<Duration> timeout = std::nullopt) const;
};

} // namespace sick::multiScan100::v2_4_4
