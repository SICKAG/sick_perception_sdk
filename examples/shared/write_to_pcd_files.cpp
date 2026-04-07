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
using ConfiguratorT = sick::multiScan100::v2_4_2_0R::Configurator;
using DriverT       = sick::multiScan100::Driver;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_2_1_0R::Configurator;
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
  auto const deviceAddress = sick::examples::getDeviceAddress(argc, argv);
  auto const basePath      = std::filesystem::current_path() / "pcd_files";

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(deviceAddress, 80);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreaming("192.168.0.100", 2115); // Enter your computer's IP address

    // Create pcd_files directory if it doesn't exist
    std::filesystem::create_directories(basePath);
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
      [basePath](sick::point_cloud::UnorganizedPointCloud const& framePointCloud) {
        auto const filePath = basePath / (std::string(kDeviceName) + "_" + std::to_string(framePointCloud.timestamp().microsecondsSinceEpoch()) + ".pcd");
        sick::pcd::writeToAsciiFile(framePointCloud, filePath.string());
      },
      config
    );

  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
