/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/drivers/Receiver/UdpScanDataReceiver.hpp>

namespace sick::multiScan100 {

//! The multiScan100 streams scan data over UDP, so the shared UDP receiver is used as-is.
using ScanDataReceiverConfig = compact::UdpScanDataReceiverConfig;
using ScanDataReceiver       = compact::UdpScanDataReceiver;

} // namespace sick::multiScan100
