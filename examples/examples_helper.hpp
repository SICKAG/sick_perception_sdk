/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/version.hpp>

#include <CLI/CLI.hpp>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <utility>

namespace sick::examples {

inline void printSdkVersion()
{
  std::cout << "This sick_perception_sdk version: " << sick::version() << '\n';
}

inline void printExceptionMessageWithPort(std::exception_ptr const& exception, std::optional<std::uint16_t> port)
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

inline void printExceptionMessage(std::exception_ptr const& exception)
{
  printExceptionMessageWithPort(exception, std::nullopt);
}

struct SensorAddress
{
  IpV4Address address;
  std::uint16_t restApiPort;
};

auto getSensorAddress(std::string exampleName, int argc, char* argv[], std::function<void(CLI::App&)> cli = [](CLI::App&) {}) -> SensorAddress
{
  CLI::App app {exampleName};
  argv = app.ensure_utf8(argv);

  std::string sensorAddressStr {"192.168.0.1"};
  std::uint16_t restApiPort = 80;
  app
    .add_option("-s,--sensor_address", sensorAddressStr, "IP address of the sensor.") //
    ->default_val(sensorAddressStr)                                                   //
    ->check(CLI::ValidIPV4);
  app.add_option("--api_port", restApiPort, "Port of the sensor's REST API.")->default_val(restApiPort)->check(CLI::Range(1, 65535));

  cli(app);

  // Do not use CLI11_PARSE here: its macro body does `return app.exit(e)` (an int),
  // which is incompatible with this function's IpV4Address return type. Exit instead.
  try
  {
    app.parse(argc, argv);
  }
  catch (CLI::ParseError const& e)
  {
    std::exit(app.exit(e));
  }

  return SensorAddress {IpV4Address(sensorAddressStr), restApiPort};
}

} // namespace sick::examples
