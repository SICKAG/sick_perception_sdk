/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
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
#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace sick::literals;
using namespace std::chrono_literals;

void onNewFrame(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::cout << "Received point cloud data with timestamp: \t" << pointCloud.timestamp() << " (" << pointCloud.numberOfPoints() << " points)\n";
}

void onNewImuData(sick::compact::imu::ImuData const& compactImu)
{
  std::cout << "Received IMU data with timestamp: \t" << compactImu.sensorTimestamp << " us\n";
}

#if defined(USE_PICOSCAN100)
void onNewEncoderData(sick::compact::encoder::EncoderData const& compactEncoder)
{
  std::cout << "Received encoder data with timestamp: \t" << compactEncoder.telegramHeader.transmitTimestamp << " us\n";
}
#endif

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  auto const deviceAddress        = sick::examples::getDeviceAddress(argc, argv);
  constexpr uint16_t scanDataPort = 2115;
  constexpr uint16_t imuPort      = 7503;
  constexpr uint16_t encoderPort  = 7504;

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(deviceAddress, 80);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreaming("192.168.0.100", scanDataPort); // Enter your computer's IP address

    std::cout << "Configuring IMU data streaming...\n";
    configurator.enableImuStreaming("192.168.0.100", imuPort); // Enter your computer's IP address

#if defined(USE_PICOSCAN100)
    std::cout << "Configuring Encoder data streaming...\n";
    configurator.enableEncoderStreaming("192.168.0.100", encoderPort); // Enter your computer's IP address
#endif
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = true;
  config.fields.enableIntensity = true;

  DriverT driver(sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver()  //
    .setup(scanDataPort) //
    .setOnNewFrameCallback(onNewFrame, config);
  driver
    .imuReceiver()  //
    .setup(imuPort) //
    .setOnNewDataCallback(onNewImuData);
#if defined(USE_PICOSCAN100)
  driver
    .encoderReceiver()  //
    .setup(encoderPort) //
    .setOnNewDataCallback(onNewEncoderData);
#endif
  driver.run();

  std::this_thread::sleep_for(10s);

  return 0;
}
