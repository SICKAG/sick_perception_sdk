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
using ConfiguratorT = sick::multiScan100::v2_4_4::Configurator;
using DriverT       = sick::multiScan100::Driver;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_3_3::Configurator;
using DriverT       = sick::picoScan100::Driver;
#endif

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <mutex>

using namespace sick::literals;
using namespace std::chrono_literals;

std::mutex output_mutex;

void onNewFrame(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received point cloud data with timestamp: \t" << pointCloud.timestamp() << " (" << pointCloud.numberOfPoints() << " points)\n";
}

void onNewImuData(sick::compact::imu::ImuData const& compactImu)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received IMU data with timestamp: \t" << compactImu.sensorTimestamp << "\n";
}

#if defined(USE_PICOSCAN100)
void onNewEncoderData(sick::compact::encoder::EncoderData const& compactEncoder)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received encoder data with timestamp: \t" << compactEncoder.telegramHeader.transmitTimestamp << "\n";
}
#endif

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  std::uint16_t scanDataPort = 2115;
  std::uint16_t imuPort      = 7503;
  std::uint16_t encoderPort  = 7504;
  sick::IpV4Address udpReceiverAddress {"192.168.0.100"};
  auto const sensorAddress = sick::examples::getSensorAddress("UDP streaming example", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--receiver_address", udpReceiverAddress, "IP address of the computer to which the sensor should send UDP data.") //
      ->default_val(udpReceiverAddress.toString())                                                                                  //
      ->check(CLI::ValidIPV4);
    app.add_option("--scan_data_port", scanDataPort, "UDP port on the computer to which the sensor should send scan data.")->default_val(scanDataPort);
    app.add_option("--imu_port", imuPort, "UDP port on the computer to which the sensor should send IMU data.")->default_val(imuPort);
#if defined(USE_PICOSCAN100)
    app.add_option("--encoder_port", encoderPort, "UDP port on the computer to which the sensor should send encoder data.")->default_val(encoderPort);
#endif
  });

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreamingCompactUdp(udpReceiverAddress, scanDataPort); // Enter your computer's IP address

    std::cout << "Configuring IMU data streaming...\n";
    configurator.enableImuStreamingCompactUdp(udpReceiverAddress, imuPort); // Enter your computer's IP address

#if defined(USE_PICOSCAN100)
    std::cout << "Configuring Encoder data streaming...\n";
    configurator.enableEncoderStreamingCompactUdp(udpReceiverAddress, encoderPort); // Enter your computer's IP address
#endif
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  sick::point_cloud::PointCloudConfiguration config;

  // Enable the desired fields in the point cloud. The enabled fields are used to convert the scan data into a point cloud. If the sensor does not provide the requested fields, the point cloud will not contain those fields.
  config.fields.enableCartesian = true;
  config.fields.enableSpherical = true;
  config.fields.enableIntensity = true;
  config.fields.enableEchoIndex = true;

  // Optionally, limit the range of the converted point cloud to a region of interest (ROI).
  config.filters.azimuth   = sick::Interval {-150_deg, 150_deg, false};
  config.filters.elevation = sick::Interval {-45_deg, 45_deg, false};

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
