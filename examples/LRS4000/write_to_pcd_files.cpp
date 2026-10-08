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

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  std::string outputDirectory = (std::filesystem::current_path() / "pcd_files").string();
  auto const sensorAddress    = sick::examples::getSensorAddress("LRS4000 PCD file example", argc, argv, [&](CLI::App& app) {
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
    sick::LRS4000::v1_10_0::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring compact streaming...\n";
    configurator.enableScanDataStreamingCompactTcp();

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

  sick::LRS4000::Driver driver(sensorAddress.address, sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver() //
    .setup()            //
    .setOnNewFrameCallback(
      [outputDirectory](sick::point_cloud::UnorganizedPointCloud const& framePointCloud) {
        auto const filePath =
          std::filesystem::path(outputDirectory) / ("LRS4000_" + std::to_string(framePointCloud.timestamp().microsecondsSinceEpoch()) + ".pcd");
        sick::pcd::writeToAsciiFile(framePointCloud, filePath.string());
      },
      config
    );

  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
