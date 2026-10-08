/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/multiScan200_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/BitmapEncoder.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudToPcdConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>
#include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std::chrono_literals;

auto getAmbientLightValueRange(sick::compact::multiscan200::MultiScan200Data const& data) -> std::pair<std::uint16_t, std::uint16_t>
{
  std::uint16_t minValue = std::numeric_limits<std::uint16_t>::max();
  std::uint16_t maxValue = std::numeric_limits<std::uint16_t>::lowest();

  for (auto value : data.ambientLightData)
  {
    if (value < minValue)
    {
      minValue = value;
    }
    if (value > maxValue)
    {
      maxValue = value;
    }
  }
  return {minValue, maxValue};
}

void writeAmbientLightToBitmap(sick::compact::multiscan200::MultiScan200Data const& data, std::string const& filename)
{
  std::vector<std::vector<std::uint16_t>> ambientLightData;
  for (std::size_t column = data.segmentMetaData.numberOfColumnsInSegment; column-- > 0;)
  {
    std::vector<std::uint16_t> columnData;
    for (std::size_t row = 0; row < data.segmentMetaData.numberOfAmbientLightRows; ++row)
    {
      auto const index = data.computeAmbientLightIndex(column, row);
      columnData.push_back(data.ambientLightData[index]);
    }
    ambientLightData.push_back(std::move(columnData));
  }

  auto const minMaxValue = getAmbientLightValueRange(data);
  auto const bitmap      = sick::encodeGrayscaleBmp<std::uint16_t>(ambientLightData, minMaxValue);
  std::ofstream file(filename, std::ios_base::binary);
  file.write(reinterpret_cast<char const*>(bitmap.data()), bitmap.size());
  file.close();
  std::cout << "Wrote ambient light bitmap with " << ambientLightData.size() << "x" << ambientLightData[0].size() << " pixels to " << filename << "\n";
}

void writePointCloudToPCDFile(sick::point_cloud::OrganizedPointCloud const& pointCloud, std::string const& filePath)
{
  sick::pcd::writeToAsciiFile(pointCloud, filePath);
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  std::string outputDirectory = (std::filesystem::current_path() / "multiScan200_files").string();
  auto const sensorAddress    = sick::examples::getSensorAddress("multiScan200 PCD/BMP file example", argc, argv, [&](CLI::App& app) {
    app
      .add_option("--output_directory", outputDirectory, "Directory to which the PCD and BMP files should be written.") //
      ->default_val(outputDirectory);
  });

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    sick::multiScan200::v1_1_0::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

    std::cout << "Configuring compact streaming...\n";
    configurator.enableScanDataStreamingCompactTcp();

    // Create output directory if it doesn't exist
    std::filesystem::create_directories(outputDirectory);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableIntensity  = true;
  config.fields.enableSpherical  = true;
  config.fields.enableRing       = true;
  config.fields.enableLayerIndex = true;
  config.fields.enableTimeOffset = true;
  config.fields.enableEchoIndex  = true;

  sick::multiScan200::Driver driver(sensorAddress.address, sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver() //
    .setup()            //
    .setOnNewFrameCallback(
      [outputDirectory](sick::point_cloud::OrganizedPointCloud const& framePointCloud) {
        auto const filename = std::filesystem::path(outputDirectory) /
                              ("multiScan200_point_cloud_" + std::to_string(framePointCloud.timestamp().microsecondsSinceEpoch()) + ".pcd");
        writePointCloudToPCDFile(framePointCloud, filename.string());
      },
      config
    )
    .setOnNewFrameCallback([outputDirectory](sick::compact::multiscan200::MultiScan200Data const& data) {
      auto const filename = std::filesystem::path(outputDirectory) /
                            ("multiScan200_ambient_light_" + std::to_string(data.telegramHeader.transmitTimestamp.microsecondsSinceEpoch()) + ".bmp");
      writeAmbientLightToBitmap(data, filename.string());
    });
  driver.run();

  std::this_thread::sleep_for(10s);
  return 0;
}
