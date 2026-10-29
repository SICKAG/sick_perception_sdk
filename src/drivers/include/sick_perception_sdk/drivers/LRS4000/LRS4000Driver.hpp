/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/drivers/LRS4000/ScanDataReceiver.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>

#include <cstdint>
#include <optional>

namespace sick::LRS4000 {

class SDK_EXPORT Config
{
public:
  static auto create(IpV4Address sensorAddress) -> Config;

  auto configureScanDataReceiver(ScanDataReceiverConfig config) -> Config&;
  //! \brief Shortcut for one point cloud per frame. Keeps the rest of an existing scan data configuration.
  auto configureScanDataReceiver(
    std::uint16_t sensorPort,
    ScanDataReceiverConfig::UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> Config&;
  //! \brief Shortcut for every frame as the parsed telegram. Keeps the rest of an existing scan data configuration.
  auto configureScanDataReceiver(std::uint16_t sensorPort, ScanDataReceiverConfig::ScanDataCallback callback) -> Config&;

  [[nodiscard]] auto scanData() const -> std::optional<ScanDataReceiverConfig> const&;
  [[nodiscard]] auto sensorAddress() const -> IpV4Address const&;

private:
  explicit Config(IpV4Address sensorAddress);

  IpV4Address m_sensorAddress;
  std::optional<ScanDataReceiverConfig> m_scanData;
};

/**
 * @ingroup Drivers
 *
 * See drivers.hpp for an overview.
 */
class SDK_EXPORT Driver
{
public:
  explicit Driver(Config const& config);

  Driver(Driver const&)                    = delete;
  auto operator=(Driver const&) -> Driver& = delete;
  Driver(Driver&&)                         = delete;
  auto operator=(Driver&&) -> Driver&      = delete;

  ~Driver();

  /**
   * @brief Connects to the TCP server and listens for incoming data packets.
   *        Forwards the received packets to the configured callbacks.
   */
  void run();

  /**
   * @brief Stops receiving data. Call @ref run() to start receiving data again.
   */
  void stop();

private:
  std::optional<ScanDataReceiver> m_scanDataReceiver;
};

} // namespace sick::LRS4000
