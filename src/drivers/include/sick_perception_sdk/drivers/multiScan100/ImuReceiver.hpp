/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/drivers/Receiver/UdpImuReceiver.hpp>

namespace sick::multiScan100 {

//! The multiScan100 streams IMU data over UDP, so the shared UDP receiver is used as-is.
using ImuReceiverConfig = compact::UdpImuReceiverConfig;
using ImuReceiver       = compact::UdpImuReceiver;

} // namespace sick::multiScan100
