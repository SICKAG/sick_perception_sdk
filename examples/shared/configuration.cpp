/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_4::Configurator;
namespace api       = sick::multiScan100::v2_4_4::api::rest;
#elif defined(USE_MULTISCAN200)
#  include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>
using ConfiguratorT = sick::multiScan200::v1_1_0::Configurator;
namespace api       = sick::multiScan200::v1_1_0::api::rest;
#elif defined(USE_LRS4000)
#  include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
using ConfiguratorT = sick::LRS4000::v1_10_0::Configurator;
namespace api       = sick::LRS4000::v1_10_0::api::rest;
#else // Default to picoScan100
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_3_3::Configurator;
namespace api       = sick::picoScan150::v2_3_3::api::rest;
#endif

#include <cstdint>
#include <iomanip>
#include <iostream>

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  sick::IpV4Address udpReceiverAddress {"192.168.0.100"};
  std::uint16_t udpReceiverPort = 2115;
  auto const sensorAddress      = sick::examples::getSensorAddress("Configuration example", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--receiver_address", udpReceiverAddress, "IP address of the computer to which the sensor should send UDP data.") //
      ->default_val(udpReceiverAddress.toString())                                                                                  //
      ->check(CLI::ValidIPV4);
    app
      .add_option("--receiver_port", udpReceiverPort, "UDP port on the computer to which the sensor should send UDP data.") //
      ->default_val(udpReceiverPort);
  });

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator {httpClient, sick::UserLevel::Service, "servicelevel"};

    std::cout << "DeviceType:      " << configurator.getDeviceType() << '\n';
    std::cout << "FirmwareVersion: " << configurator.getFirmwareVersion() << '\n';
    std::cout << "LocationName:    " << configurator.getLocationName() << '\n';
    std::cout << "OrderNumber:     " << configurator.getOrderNumber() << '\n';
    std::cout << "SerialNumber:    " << configurator.getSerialNumber() << '\n';
    std::cout << "SystemTime:      " << configurator.getSystemTimeOfSensor().microsecondsSinceEpoch() << " us since epoch\n";
    std::cout << "IpAddress:       " << sick::IpV4Address(configurator.getEtherIPAddress()) << '\n';
    std::cout << "OpHours:         " << configurator.getOpHours() << '\n';

    std::cout << "Setting echo filter...\n";
    configurator.setFREchoFilter(api::FREchoFilter::Post::Request::FREchoFilter::FirstEcho);

    std::cout << "Configuring compact streaming...\n";
#if defined(USE_LRS4000) || defined(USE_MULTISCAN200)
    configurator.enableScanDataStreamingCompactTcp();
#else
    configurator.enableScanDataStreamingCompactUdp(udpReceiverAddress, udpReceiverPort);
#endif
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
