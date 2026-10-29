/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/multiScan100/ImuReceiver.hpp>
#include <sick_perception_sdk/drivers/multiScan100/ScanDataReceiver.hpp>

#include <cstdint>
#include <optional>

namespace sick::multiScan100 {

/**
 * @brief Selects which receivers a @ref Driver creates and how each of them is configured.
 *
 * A receiver that is not configured here is not created by the driver at all.
 */
class SDK_EXPORT Config
{
public:
  static auto create() -> Config;

  auto configureScanDataReceiver(ScanDataReceiverConfig config) -> Config&;
  //! \brief Shortcut for one point cloud per frame. Keeps the rest of an existing scan data configuration.
  auto configureScanDataReceiver(
    std::uint16_t receiverPort,
    ScanDataReceiverConfig::UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> Config&;
  //! \brief Shortcut for every segment as the parsed telegram. Keeps the rest of an existing scan data configuration.
  auto configureScanDataReceiver(std::uint16_t receiverPort, ScanDataReceiverConfig::ScanDataCallback callback) -> Config&;

  auto configureImuReceiver(ImuReceiverConfig config) -> Config&;
  auto configureImuReceiver(std::uint16_t receiverPort, ImuReceiverConfig::DataCallback callback) -> Config&;

  [[nodiscard]] auto scanData() const -> std::optional<ScanDataReceiverConfig> const&;
  [[nodiscard]] auto imu() const -> std::optional<ImuReceiverConfig> const&;

private:
  Config() = default;

  std::optional<ScanDataReceiverConfig> m_scanData;
  std::optional<ImuReceiverConfig> m_imu;
};

/**
 * @ingroup Drivers
 *
 * See drivers.hpp for an overview.
 */
class SDK_EXPORT Driver
{
public:
  //! \brief Creates exactly those receivers that @p config configures.
  explicit Driver(Config const& config);

  Driver(Driver const&)                    = delete;
  auto operator=(Driver const&) -> Driver& = delete;
  Driver(Driver&&)                         = delete;
  auto operator=(Driver&&) -> Driver&      = delete;

  ~Driver();

  /**
   * @brief Listens for incoming data packets.
   *        Forwards the received packets to the configured callbacks.
   */
  void run();

  /**
   * @brief Stops receiving data. Call @ref run() to start receiving data again.
   */
  void stop();

private:
  std::optional<ScanDataReceiver> m_scanDataReceiver;
  std::optional<ImuReceiver> m_imuReceiver;
};

} // namespace sick::multiScan100
