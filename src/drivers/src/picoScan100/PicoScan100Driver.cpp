/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>

#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace sick::picoScan100 {

Driver::Driver(std::function<void(std::exception_ptr)> const& onError)
  : m_encoderReceiver(onError, "EncoderReceiver")
  , m_imuReceiver(onError, "ImuReceiver")
  , m_scanDataReceiver(onError, "ScanDataReceiver")
{ }

Driver::~Driver()
{
  stop();
}

void Driver::run()
{
  m_encoderReceiver.start();
  m_imuReceiver.start();
  m_scanDataReceiver.start();
}

void Driver::stop()
{
  m_encoderReceiver.stop();
  m_imuReceiver.stop();
  m_scanDataReceiver.stop();
}

// --------------------------------------------------------------
// EncoderReceiver
// --------------------------------------------------------------
auto Driver::EncoderReceiver::setup(
  std::uint16_t receiverPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> EncoderReceiver&
{
  BaseT::setup(
    [this](compact::encoder::EncoderData const& data) {
      if (m_callback.has_value())
      {
        (*m_callback)(data);
      }
    },
    receiverPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );

  return *this;
}

auto Driver::EncoderReceiver::setOnNewDataCallback(DataCallback callback) -> EncoderReceiver&
{
  m_callback = std::move(callback);
  return *this;
}

} // namespace sick::picoScan100
