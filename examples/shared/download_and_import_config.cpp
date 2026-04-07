/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_2_0R::Configurator;
#else // Default to picoScan150
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_2_1_0R::Configurator;
#endif

#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono_literals;

static void writeToFile(std::string const& filePath, std::string const& content)
{
  std::ofstream file(filePath, std::ios::binary);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not open file for writing: " + filePath);
  }
  file.write(content.data(), static_cast<std::streamsize>(content.size()));
}

static auto readFileContent(std::string const& filePath) -> std::string
{
  std::ifstream file(filePath, std::ios::binary);
  if (!file.is_open())
  {
    throw std::runtime_error("Could not open file: " + filePath);
  }
  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
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
    std::cout << "Device type: " << configurator.deviceType.get() << '\n';

    std::cout << "Creating backup\n";
    configurator.post("CreateParameterBackup").withRequestPayload("Passphrase", std::string("test")).execute();
    // Creating the backup is asynchronous; wait for it to complete
    std::this_thread::sleep_for(1s);

    auto const backupContent         = httpClient->get("/api/parameterbackup");
    std::string const backupFilePath = "parameterbackup.json";
    writeToFile(backupFilePath, backupContent);
    std::cout << "Backup saved to " << backupFilePath << " (" << backupContent.size() << " bytes)\n";

    std::cout << "LocationName: " << configurator.locationName.get() << '\n';
    configurator.locationName.set("import_config_test");
    std::cout << "LocationName changed to: " << configurator.locationName.get() << '\n';

    std::cout << "Uploading backup\n";
    auto const fileContent = readFileContent(backupFilePath);
    auto const putResult   = httpClient->client().Put("/api/parameterbackup", fileContent, "application/octet-stream");
    if (!putResult || putResult->status != 200)
    {
      auto const status = putResult ? std::to_string(putResult->status) : "no response";
      throw std::runtime_error("PUT /api/parameterbackup failed: " + status);
    }
    std::cout << "Backup uploaded\n";

    std::cout << "Restoring backup\n";
    configurator.post("RestoreParameterBackup").withRequestPayload("Passphrase", std::string("test")).execute();
    // The restore is asynchronous; wait for it to complete
    std::this_thread::sleep_for(1s);
    std::cout << "Backup restored\n";

    // Optionally, persist the restored parameters on the device.
    // If this is not done, the restored parameters will be lost after a power cycle.
    configurator.persistParametersOnDevice();
    std::cout << "Parameters persisted\n";

    std::cout << "LocationName after restore: " << configurator.locationName.get() << '\n';
  }
  catch (std::exception const& e)
  {
    std::cout << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
