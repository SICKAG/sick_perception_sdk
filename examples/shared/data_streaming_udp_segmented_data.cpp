/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_4::Configurator;
using DriverT       = sick::multiScan100::Driver;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_3_3::Configurator;
using DriverT       = sick::picoScan100::Driver;
#endif

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

void onNewScanData(sick::compact::scan_data::ScanData const& data)
{
  std::cout << "Received scan data with telegram sequence number: " << data.telegramHeader.telegramSequenceNumber << '\n';
  for (auto const& module : data.modules)
  {
    std::cout << "Number of Layers: " << module.rowMetaData.size() << '\n';
  }
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  sick::IpV4Address udpReceiverAddress {"192.168.0.100"};
  std::uint16_t scanDataPort = 2115;
  auto const sensorAddress   = sick::examples::getSensorAddress("Segmented data streaming example", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--receiver_address", udpReceiverAddress, "IP address of the computer to which the sensor should send UDP data.") //
      ->default_val(udpReceiverAddress.toString())                                                                                  //
      ->check(CLI::ValidIPV4);
    app
      .add_option("--scan_data_port", scanDataPort, "UDP port on the computer to which the sensor should send scan data.") //
      ->default_val(scanDataPort);
  });

  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  try
  {
    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreamingCompactUdp(udpReceiverAddress, scanDataPort);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  DriverT driver(sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver() //
    .setup()            //
    .setOnNewSegmentCallback(onNewScanData);
  driver.run();

  std::this_thread::sleep_for(10s);

  return 0;
}
