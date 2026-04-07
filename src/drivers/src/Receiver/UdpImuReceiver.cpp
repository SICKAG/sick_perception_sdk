/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpImuReceiver.hpp>

namespace sick::compact {

auto UdpImuReceiver::setup(
  std::uint16_t receiverPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> UdpImuReceiver&
{
  BaseT::setup(
    [this](imu::ImuData const& data) {
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

auto UdpImuReceiver::setOnNewDataCallback(DataCallback callback) -> UdpImuReceiver&
{
  m_callback = std::move(callback);
  return *this;
}

} // namespace sick::compact
