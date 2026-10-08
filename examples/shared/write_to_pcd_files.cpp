/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudToPcdConverter.hpp>
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

#include <filesystem>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

#if defined(USE_MULTISCAN100)
constexpr char const* kDeviceName = "multiScan100";
#else
constexpr char const* kDeviceName = "picoScan100";
#endif

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  sick::IpV4Address udpReceiverAddress {"192.168.0.100"};
  std::uint16_t scanDataPort  = 2115;
  std::string outputDirectory = (std::filesystem::current_path() / "pcd_files").string();
  auto const sensorAddress    = sick::examples::getSensorAddress("PCD file example", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--receiver_address", udpReceiverAddress, "IP address of the computer to which the sensor should send UDP data.") //
      ->default_val(udpReceiverAddress.toString())                                                                                  //
      ->check(CLI::ValidIPV4);
    app
      .add_option("--scan_data_port", scanDataPort, "UDP port on the computer to which the sensor should send scan data.") //
      ->default_val(scanDataPort);
    app
      .add_option("--output_directory", outputDirectory, "Directory to which the PCD files should be written.") //
      ->default_val(outputDirectory);
  });

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreamingCompactUdp(udpReceiverAddress, scanDataPort);

    // Create pcd_files directory if it doesn't exist
    std::filesystem::create_directories(outputDirectory);
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
    .scanDataReceiver() //
    .setup()            //
    .setOnNewFrameCallback(
      [outputDirectory](sick::point_cloud::UnorganizedPointCloud const& framePointCloud) {
        auto const filePath = std::filesystem::path(outputDirectory) /
                              (std::string(kDeviceName) + "_" + std::to_string(framePointCloud.timestamp().microsecondsSinceEpoch()) + ".pcd");
        sick::pcd::writeToAsciiFile(framePointCloud, filePath.string());
      },
      config
    );

  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
