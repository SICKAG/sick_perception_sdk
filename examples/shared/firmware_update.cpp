/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_4::Configurator;
namespace api       = sick::multiScan100::v2_4_4::api::rest;
#elif defined(USE_MULTISCAN200)
#  include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>
using ConfiguratorT = sick::multiScan200::v1_1_0::Configurator;
namespace api       = sick::multiScan200::v1_1_0::api::rest;
#else // Default to picoScan100
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_3_3::Configurator;
namespace api       = sick::picoScan150::v2_3_3::api::rest;
#endif

#include <CLI/CLI.hpp>
#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace sick::literals;

void waitForDeviceReboot(ConfiguratorT& configurator, std::uint32_t bootCountBeforeUpdate, sick::Duration const timeout)
{
  auto const startTime = sick::Timestamp::now();
  while (true)
  {
    auto const elapsedTime = sick::Timestamp::now() - startTime;
    if (elapsedTime > timeout)
    {
      throw std::runtime_error("Waiting for device reboot timed out after " + std::to_string(elapsedTime.seconds()) + " seconds.");
    }

    try
    {
      if (configurator.getPowerOnCnt() > bootCountBeforeUpdate)
      {
        return;
      }
    }
    catch (...)
    { }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  std::string filePath     = "";
  auto const sensorAddress = sick::examples::getSensorAddress("Firmware update example", argc, argv, [&filePath](CLI::App& app) {
    app.add_option("-f,--file", filePath, "Path of the firmware file (*.spk.signed, *.swp).")->required()->check(CLI::ExistingFile);
  });

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator {httpClient, sick::UserLevel::Service, "servicelevel"};

    std::cout << "DeviceType:                     " << configurator.getDeviceType() << '\n';
    std::cout << "Firmware version before update: " << configurator.getFirmwareVersion() << '\n';

    // Read the boot count from the sensor. This will tell us if the sensor has rebooted after the firmware update.
    auto const bootCountBeforeUpdate = configurator.getPowerOnCnt();

    constexpr auto updateTimeout = 5_min;
    std::cout << "Updating firmware with " << updateTimeout.seconds() << " seconds timeout from file " << filePath << ".\n";
    std::cout << "DO NOT POWER OFF THE SENSOR DURING THE UPDATE!\n";
    std::cout << "There may be error messages 'Could not establish connection' in the log during the update process.\n";
    configurator.updateFirmware(filePath, updateTimeout);
    std::cout << "Firmware update done. The sensor will restart now.\n";

    constexpr auto rebootTimeout = 1_min;
    std::cout << "Waiting max. " << rebootTimeout.seconds() << " seconds for device to restart...\n";
    waitForDeviceReboot(configurator, bootCountBeforeUpdate, rebootTimeout);

    std::cout << "Firmware version after update: " << configurator.getFirmwareVersion() << '\n';
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
