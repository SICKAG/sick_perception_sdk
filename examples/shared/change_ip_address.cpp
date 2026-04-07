/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SensorConfigurator.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT = sick::multiScan100::v2_4_2_0R::Configurator;
#elif defined(USE_LRS4000)
#  include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
using ConfiguratorT = sick::LRS4000::v1_9_1_0R::Configurator;
#else // Default to picoScan100
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT = sick::picoScan150::v2_2_1_0R::Configurator;
#endif

#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace sick::literals;
using namespace std::chrono_literals;

/**
 * @brief Wait until the sensor is reachable at the given address.
 * 
 * This is useful after changing the sensor's IP address and applying the changes, as the sensor will reboot and be temporarily unreachable during that process.
 * The presence of the sensor is checked by sending HTTP GET requests to the endpoint `/`.
 */
void waitForSensor(sick::IpV4Address const& address)
{
  // Create socket and wait until the sensor is reachable at the given address
  constexpr int maxRetries = 30;
  int retry                = 0;
  for (; retry < maxRetries; ++retry)
  {
    try
    {
      std::cout << "." << std::flush;
      sick::httplib_client::HttpClient httpClient(address, 80);
      httpClient.disableErrorLogging(); // Disable error logging to avoid cluttering the output with expected connection errors during the sensor reboot
      httpClient.get("/");              // Try to send a simple HTTP request to check if the sensor is reachable
      break;                            // If the request succeeds, break the loop
    }
    catch (std::exception const&)
    {
      std::this_thread::sleep_for(1s); // Wait before retrying
    }
  }

  if (retry == maxRetries)
  {
    throw std::runtime_error("Sensor is not reachable at " + address.toString() + " after " + std::to_string(maxRetries) + " attempts");
  }
}

/**
 * @brief Change the sensor's IP address and verify that the sensor is reachable at the new address.
 */
void changeAddress(sick::IpV4Address const& oldAddress, sick::IpV4Address const& newAddress)
{
  sick::IpV4Address const netMask        = "255.255.255.0";
  sick::IpV4Address const gatewayAddress = "0.0.0.0";

  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(oldAddress, 80);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  std::cout << "Current IP Address: " << configurator.sensorIPAddress.get().toString() << '\n';

  // Write new IP configuration
  std::cout << "Configuring new IP settings...\n";
  configurator.sensorIPAddressingMode.set(ConfiguratorT::IPAddressingMode::StaticIP);
  configurator.sensorIPAddress.set(newAddress);
  configurator.sensorIPMask.set(netMask);
  configurator.sensorIPGateway.set(gatewayAddress);

  // Read back and print the new configuration
  auto const modeResponse = configurator.sensorIPAddressingMode.get();
  std::cout << "New IP Configuration:\n";
  std::cout << "    - IP Mode: " << (modeResponse == ConfiguratorT::IPAddressingMode::StaticIP ? "Static" : "DHCP") << '\n';
  std::cout << "    - IP Address: " << configurator.sensorIPAddress.get().toString() << '\n';
  std::cout << "    - IP Mask: " << configurator.sensorIPMask.get().toString() << '\n';
  std::cout << "    - IP Gateway: " << configurator.sensorIPGateway.get().toString() << '\n';

  // Apply the changes
  std::cout << "Applying IP configuration changes...\n";
#if defined(USE_LRS4000)
  // The following call will log an error message.
  // This is expected behavior for LRS4000 sensors when changing the IP address
  // because the sensor will disconnect before the configuration change is applied.
  // Error logging will be disabled for this command to avoid cluttering the output.
  httpClient->disableErrorLogging();
#endif
  configurator.ethernetUpdate.apply();
#if defined(USE_LRS4000)
  httpClient->enableErrorLogging();
#endif

  std::cout << "IP configuration updated. Waiting for sensor";
  waitForSensor(newAddress);
  std::cout << "\n";

  // Connect with new IP address
  auto const httpClientNew = std::make_shared<sick::httplib_client::HttpClient>(newAddress, 80);
  ConfiguratorT configuratorNew(httpClientNew, sick::UserLevel::Service, "servicelevel");
  std::cout << "Connected to sensor at new IP: " << configuratorNew.sensorIPAddress.get().toString() << '\n';
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  auto const [oldAddress, newAddress] = sick::examples::getTwoDeviceAddresses(argc, argv);

  try
  {
    std::cout << "Changing address from " << oldAddress.toString() << " to " << newAddress.toString()
              << " and verify that the device is reachable at the new address.\n";
    changeAddress(oldAddress, newAddress);

    std::cout << "\nChanging address back to " << oldAddress.toString() << " so the sensor is available at the default address for other examples.\n";
    changeAddress(newAddress, oldAddress);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  return 0;
}
