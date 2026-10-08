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

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;

std::mutex output_mutex;

void onNewFrame1(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received frame from device 1 containing " << pointCloud.numberOfPoints() << " points.\n";
}

void onNewFrame2(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received frame from device 2 containing " << pointCloud.numberOfPoints() << " points.\n";
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  sick::IpV4Address secondSensorAddress {"192.168.0.2"};
  sick::IpV4Address udpReceiverAddress {"192.168.0.100"};
  std::uint16_t compactStreamingPortSensor1 = 2115;
  std::uint16_t compactStreamingPortSensor2 = 2116;
  auto const sensorAddress1                 = sick::examples::getSensorAddress("UDP streaming example with two devices", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--sensor_address_2", secondSensorAddress, "IP address of the second sensor.") //
      ->default_val(secondSensorAddress.toString())                                              //
      ->check(CLI::ValidIPV4);
    app
      .add_option("--port1", compactStreamingPortSensor1, "UDP receiver port for scan data from sensor 1.") //
      ->default_val(compactStreamingPortSensor1);
    app
      .add_option("--port2", compactStreamingPortSensor2, "UDP receiver port for scan data from sensor 2.") //
      ->default_val(compactStreamingPortSensor2);
    app
      .add_option("--receiver_address", udpReceiverAddress, "IP address of the computer to which the sensors should send UDP data.") //
      ->default_val(udpReceiverAddress.toString())
      ->check(CLI::ValidIPV4);
  });

  auto const httpClient1 = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress1.address, sensorAddress1.restApiPort);
  auto const httpClient2 = std::make_shared<sick::httplib_client::HttpClient>(secondSensorAddress, sensorAddress1.restApiPort);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  ConfiguratorT configurator1(httpClient1, sick::UserLevel::Service, "servicelevel");
  ConfiguratorT configurator2(httpClient2, sick::UserLevel::Service, "servicelevel");

  try
  {
    std::cout << "Sensor 1 address: " << sick::IpV4Address(configurator1.getEtherIPAddress()) << '\n';
    std::cout << "Sensor 2 address: " << sick::IpV4Address(configurator2.getEtherIPAddress()) << '\n';

    std::cout << "Configuring scan data streaming...\n";
    configurator1.enableScanDataStreamingCompactUdp(udpReceiverAddress, compactStreamingPortSensor1);
    configurator2.enableScanDataStreamingCompactUdp(udpReceiverAddress, compactStreamingPortSensor2);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  DriverT driver1([&](std::exception_ptr const& exception) {
    std::lock_guard<std::mutex> lock(output_mutex);
    sick::examples::printExceptionMessageWithPort(exception, 2115);
  });
  DriverT driver2([&](std::exception_ptr const& exception) {
    std::lock_guard<std::mutex> lock(output_mutex);
    sick::examples::printExceptionMessageWithPort(exception, 2116);
  });

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = true;
  config.fields.enableIntensity = true;

  driver1
    .scanDataReceiver() //
    .setup(2115)        //
    .setOnNewFrameCallback(onNewFrame1, config);
  driver1.run();

  driver2
    .scanDataReceiver() //
    .setup(2116)        //
    .setOnNewFrameCallback(onNewFrame2, config);
  driver2.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
