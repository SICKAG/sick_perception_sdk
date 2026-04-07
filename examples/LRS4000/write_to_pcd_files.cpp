/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/LRS4000_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudToPcdConverter.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>

#include <filesystem>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

constexpr char const* kDeviceName = "LRS4000";

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
    sick::LRS4000::v1_9_1_0R::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring compact streaming...\n";
    configurator.streaming.set(sick::LRS4000::v1_9_1_0R::Configurator::StreamingMode::Compact);

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

  sick::LRS4000::Driver driver(deviceAddress, sick::examples::printExceptionMessage);
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
