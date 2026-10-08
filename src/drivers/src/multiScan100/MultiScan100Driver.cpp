/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>

#include <exception>
#include <functional>

namespace sick::multiScan100 {

Driver::Driver(std::function<void(std::exception_ptr const&)> const& onError)
  : m_imuReceiver(onError, "ImuReceiver")
  , m_scanDataReceiver(onError, "ScanDataReceiver")
{ }

Driver::~Driver()
{
  stop();
}

void Driver::run()
{
  m_imuReceiver.start();
  m_scanDataReceiver.start();
}

void Driver::stop()
{
  m_imuReceiver.stop();
  m_scanDataReceiver.stop();
}

} // namespace sick::multiScan100
