/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
using ConfiguratorT = sick::LRS4000::v1_9_1_0R::Configurator;
using DriverT       = sick::LRS4000::Driver;

#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

void onNewPointCloud(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::cout << "Got point cloud with " << pointCloud.numberOfPoints() << " points.\n";
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  auto const deviceAddress = sick::examples::getDeviceAddress(argc, argv);

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(deviceAddress, 80);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring compact streaming...\n";
    configurator.streaming.set(ConfiguratorT::StreamingMode::Compact);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = true;
  config.fields.enableIntensity = true;

  DriverT driver(deviceAddress, sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver() //
    .setup()            //
    .setOnNewFrameCallback(std::function<void(sick::point_cloud::UnorganizedPointCloud const&)> {onNewPointCloud}, config);
  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
