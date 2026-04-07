/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#  include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_2_0R::Configurator;
using DriverT       = sick::multiScan100::Driver;
#elif defined(USE_LRS4000)
#  include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#  include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
using ConfiguratorT = sick::LRS4000::v1_9_1_0R::Configurator;
using DriverT       = sick::LRS4000::Driver;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_2_1_0R::Configurator;
using DriverT       = sick::picoScan100::Driver;
#endif

#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace sick::literals;
using namespace std::chrono_literals;

void onNewPointCloudData(sick::point_cloud::UnorganizedPointCloud const& pointCloud)
{
  using FieldType = sick::point_cloud::PointField::FieldType;
  std::cout << "Received point cloud data with timestamp: " << pointCloud.timestamp() << " (" << pointCloud.numberOfPoints() << " points)\n";

  for (size_t i = 0; i < pointCloud.numberOfPoints(); ++i)
  {
    auto const [x, y, z]                   = pointCloud.getCartesian(i);
    auto const [range, azimuth, elevation] = pointCloud.getSpherical(i);
    auto const echo                        = pointCloud.getEcho(i);

    std::cout << "Point " << i << ":\t" << "x=" << std::fixed << std::setprecision(3) << x << " m\t" << "y=" << y << " m\t" << "z=" << z << " m\t"
              << "range=" << range << " m\t" << "echo=" << static_cast<int>(echo) << '\n';
  }
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

    std::cout << "Configuring scan data streaming...\n";
#if defined(USE_LRS4000)
    configurator.streaming.set(ConfiguratorT::StreamingMode::Compact);
#else
    configurator.enableScanDataStreaming("192.168.0.100", 2115); // Enter your computer's IP address
#endif
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = true;
  config.fields.enableSpherical = true;
  config.fields.enableIntensity = true;
  config.fields.enableEchoIndex = true;
  // only output data in this ROI
  config.filters.azimuth   = sick::Interval {-1_deg, 1_deg, false};
  config.filters.elevation = sick::Interval {-1_deg, 1_deg, false};

#if defined(USE_LRS4000)
  DriverT driver(deviceAddress, sick::examples::printExceptionMessage);
#else
  DriverT driver(sick::examples::printExceptionMessage);
#endif
  driver
    .scanDataReceiver()   //
    .setup(2115, 10s, 3s) //
    .setOnNewFrameCallback(std::function<void(sick::point_cloud::UnorganizedPointCloud const&)> {onNewPointCloudData}, config);
  driver.run();
  std::this_thread::sleep_for(10s);
  return 0;
}
