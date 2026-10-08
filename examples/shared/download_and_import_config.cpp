/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_4::Configurator;
#elif defined(USE_MULTISCAN200)
#  include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>
using ConfiguratorT = sick::multiScan200::v1_1_0::Configurator;
#else // Default to picoScan150
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_3_3::Configurator;
using EndpointsT    = sick::picoScan150::v2_3_3::Endpoints;
#endif

#include <CLI/CLI.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>

using namespace std::chrono_literals;
using namespace sick::literals;

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  std::string filePath;
  std::string passPhrase  = "";
  bool downloadFromSensor = false, importIntoSensor = false;
  auto const sensorAddress = sick::examples::getSensorAddress("Download and import configuration example", argc, argv, [&](CLI::App& app) {
    app.add_option("-f,--file", filePath, "Path of the configuration backup file.")->required();
    app.add_option("-p,--passphrase", passPhrase, "Passphrase for the configuration backup.")->default_val(passPhrase);
    app.add_flag("-d,--download", downloadFromSensor, "Download a configuration backup from the sensor to a file.");
    app.add_flag("-i,--import", importIntoSensor, "Import a configuration backup from a file into the sensor.");
  });

  if (!downloadFromSensor && !importIntoSensor)
  {
    std::cout << "Error: At least one of --download or --import must be specified.\n";
    return EXIT_FAILURE;
  }

  try
  {
    auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

    // Change the default passwords during initial commissioning to secure your device.
    // Passwords can be updated via the web browser or API.
    // For production use, store passwords in a secure vault rather than in plain text.
    ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");
    std::cout << "Device type: " << configurator.getDeviceType() << '\n';

    constexpr auto timeout = 5_s;

    if (downloadFromSensor)
    {
      std::cout << "\nLocation name before backup: " << configurator.getLocationName() << '\n';
      std::cout << "Creating backup with " << timeout.seconds() << " seconds timeout.\n";
      auto const backupResult = configurator.backupParameters(passPhrase, timeout);

      std::cout << "Dumping backup to " << filePath << '\n';
      std::ofstream backupFile(filePath, std::ios::binary);
      backupFile << backupResult;
      backupFile.close();
    }
    if (importIntoSensor)
    {
      std::cout << "\nOverwriting location name to demonstrate restore...\n";
      configurator.setLocationName("Temporary location name");
      std::cout << "Location name after overwrite: " << configurator.getLocationName() << '\n';

      std::cout << "Reading backup from " << filePath << '\n';
      std::ifstream backupFile(filePath, std::ios::binary);
      std::string const backupResult((std::istreambuf_iterator<char>(backupFile)), std::istreambuf_iterator<char>());
      backupFile.close();

      std::cout << "Restoring backup with " << timeout.seconds() << " seconds timeout.\n";
      configurator.restoreParameters(backupResult, passPhrase, timeout);

      std::cout << "LocationName after restore: " << configurator.getLocationName() << '\n';
    }
  }
  catch (std::exception const& e)
  {
    std::cout << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
