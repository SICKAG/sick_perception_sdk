/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>

namespace sick::compact {

using ErrorCallback = std::function<void(std::exception_ptr const&)>;

struct ReceiverTransport
{
  std::uint16_t port;
  std::chrono::milliseconds firstDataTimeout;
  std::chrono::milliseconds newDataTimeout;
  std::size_t receiveBufferSize;
};

namespace receiver_defaults {

inline constexpr std::chrono::milliseconds kFirstDataTimeout {3000};
inline constexpr std::chrono::milliseconds kNewDataTimeout {1000};

//! Maximum payload of a single UDP datagram.
inline constexpr std::size_t kUdpReceiveBufferSize = 65'507;
inline constexpr std::size_t kTcpReceiveBufferSize = 4'000'000;

inline ErrorCallback const kDefaultErrorCallback = [](std::exception_ptr const& exception) -> void {
  std::rethrow_exception(exception);
};

} // namespace receiver_defaults

} // namespace sick::compact
