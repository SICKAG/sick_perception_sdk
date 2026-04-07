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
using ConfiguratorT = sick::multiScan100::v2_4_2_0R::Configurator;
using DriverT       = sick::multiScan100::Driver;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_2_1_0R::Configurator;
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
  auto const deviceAddresses = sick::examples::getTwoDeviceAddresses(argc, argv);

  auto const httpClient1 = std::make_shared<sick::httplib_client::HttpClient>(deviceAddresses.first, 80);
  auto const httpClient2 = std::make_shared<sick::httplib_client::HttpClient>(deviceAddresses.second, 80);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  ConfiguratorT configurator1(httpClient1, sick::UserLevel::Service, "servicelevel");
  ConfiguratorT configurator2(httpClient2, sick::UserLevel::Service, "servicelevel");

  try
  {
    std::cout << "Device 1 IP: " << configurator1.sensorIPAddress.get().toString() << '\n';
    std::cout << "Device 2 IP: " << configurator2.sensorIPAddress.get().toString() << '\n';

    std::cout << "Configuring scan data streaming...\n";
    configurator1.enableScanDataStreaming("192.168.0.100", 2115); // Enter your computer's IP address
    configurator2.enableScanDataStreaming("192.168.0.100", 2116); // Enter your computer's IP address
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  DriverT driver1([&](std::exception_ptr exception) {
    std::lock_guard<std::mutex> lock(output_mutex);
    sick::examples::printExceptionMessageWithPort(exception, 2115);
  });
  DriverT driver2([&](std::exception_ptr exception) {
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
