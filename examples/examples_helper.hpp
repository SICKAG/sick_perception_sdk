/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/version.hpp>

#include <cstdint>
#include <exception>
#include <iostream>
#include <optional>
#include <utility>

namespace sick::examples {

inline void printSdkVersion()
{
  std::cout << "SDK Version: " << sick::version() << '\n';
}

inline void printExceptionMessageWithPort(std::exception_ptr exception, std::optional<std::uint16_t> port)
{
  try
  {
    if (exception)
    {
      std::rethrow_exception(exception);
    }
  }
  catch (std::exception const& exception)
  {
    if (port.has_value())
    {
      std::cout << "Error on port " << port.value() << ": " << exception.what() << '\n';
    }
    else
    {
      std::cout << "Error: " << exception.what() << '\n';
    }
  }
}

inline void printExceptionMessage(std::exception_ptr exception)
{
  printExceptionMessageWithPort(exception, std::nullopt);
}

auto getDeviceAddress(int argc, char* argv[]) -> IpV4Address
{
  if (argc == 2)
  {
    return sick::IpV4Address(argv[1]);
  }
  return sick::IpV4Address("192.168.0.1");
}

auto getTwoDeviceAddresses(int argc, char* argv[]) -> std::pair<IpV4Address, IpV4Address>
{
  if (argc == 3)
  {
    return {sick::IpV4Address(argv[1]), sick::IpV4Address(argv[2])};
  }
  return {sick::IpV4Address("192.168.0.1"), sick::IpV4Address("192.168.0.2")};
}

} // namespace sick::examples
