/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_LRS4000)
#  include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
using ConfiguratorT = sick::LRS4000::v1_10_0::Configurator;
using DriverT       = sick::LRS4000::Driver;
#else // Defaults to multiScan200
#  include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>
using ConfiguratorT = sick::multiScan200::v1_1_0::Configurator;
using DriverT       = sick::multiScan200::Driver;
#endif

#include <chrono>
#include <iostream>
#include <mutex>

using namespace sick::literals;
using namespace std::chrono_literals;

std::mutex output_mutex;

#if defined(USE_MULTISCAN200)
void onNewAmbientLightData(sick::compact::ambient_light::AmbientLightData const& compactAmbientLight)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received ambient light data with timestamp: " << compactAmbientLight.payload.metaData.startTimestamp << "\n";
}

void onNewImuData(sick::compact::imu::ImuData const& compactImu)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Received IMU data with timestamp: \t" << compactImu.sensorTimestamp << "\n";
}
#endif

void onNewPointCloud(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Got point cloud with " << pointCloud.numberOfPoints() << " points.\n";
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  auto const sensorAddress = sick::examples::getSensorAddress("TCP streaming example with drivers", argc, argv);

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring compact streaming...\n";
    configurator.enableScanDataStreamingCompactTcp();
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

  DriverT driver(sensorAddress.address, sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver() //
    .setup()            //
    .setOnNewFrameCallback(std::function<void(sick::point_cloud::UnorganizedPointCloud const&)> {onNewPointCloud}, config);
#if defined(USE_MULTISCAN200)
  driver
    .ambientLightReceiver() //
    .setup()                //
    .setOnNewDataCallback(onNewAmbientLightData);
  driver
    .imuReceiver() //
    .setup()       //
    .setOnNewDataCallback(onNewImuData);
#endif
  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
