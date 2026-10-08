/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/LRS4000_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>

#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace sick::literals;
using namespace std::chrono_literals;

std::mutex output_mutex;

std::uint8_t numberOfScans = 0;

void onNewScanData(sick::compact::scan_data::ScanData const& data)
{
  numberOfScans++;
  if (numberOfScans == 100)
  {
    std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << "Received scan data with telegram sequence number: " << data.telegramHeader.telegramSequenceNumber << '\n';
    numberOfScans = 0;
  }
}

void onDataLoss(sick::compact::LossCounts const& lossCounts)
{
  std::lock_guard<std::mutex> lock(output_mutex);
  std::cout << "Data losses detected: lost telegrams=" << lossCounts.numberOfLostTelegrams << ", lost frames=" << lossCounts.numberOfLostFrames
            << ", lost segments=" << lossCounts.numberOfLostSegments << '\n';
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  auto const sensorAddress = sick::examples::getSensorAddress("LRS4000 diagnosis example", argc, argv);

  sick::Log::init(sick::LogLevel::Info);

  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  sick::LRS4000::v1_10_0::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  try
  {
    auto const sensorAddress = sick::IpV4Address(configurator.getEtherIPAddress());
    std::cout << "Diagnosis for device at " << sensorAddress << '\n';
    std::cout << "You can find a diagnosis overview at: http://" << sensorAddress << "/#/diagnosis/overview\n";
    std::cout << "DeviceType:      " << configurator.getDeviceType() << '\n';
    std::cout << "FirmwareVersion: " << configurator.getFirmwareVersion() << '\n';
    std::cout << "LocationName:    " << configurator.getLocationName() << '\n';
    std::cout << "OrderNumber:     " << configurator.getOrderNumber() << '\n';
    std::cout << "SerialNumber:    " << configurator.getSerialNumber() << '\n';
    std::cout << "SystemTime:      " << configurator.getSystemTimeOfSensor().microsecondsSinceEpoch() << " us since epoch\n";

    std::cout << "Blinking the device LEDs for identification...\n";
    configurator.findMe(5); // Blink for 5 seconds

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreamingCompactTcp();
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }

  // gets continuously DeviceState and Temperature
  std::thread deviceHealthThread([&configurator]() {
    while (true)
    {
      try
      {
        auto const deviceState       = static_cast<int>(configurator.getDeviceStatus());
        auto const temperature       = configurator.getCurrentTempDev();
        auto const contaminationData = configurator.getContaminationData();

        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "DeviceState: " << deviceState << '\n';
        std::cout << "Temperature: " << temperature << '\n';

        std::cout << "ContaminationData [" << contaminationData.size() << " sectors]: ";
        for (size_t i = 0; i < contaminationData.size(); ++i)
        {
          std::cout << contaminationData[i];
          if (i < contaminationData.size() - 1)
          {
            std::cout << ", ";
          }
        }
        std::cout << '\n';
      }
      catch (std::exception const& exception)
      {
        std::lock_guard<std::mutex> lock(output_mutex);
        std::cout << "Polling error: " << exception.what() << '\n';
      }
      std::this_thread::sleep_for(2s);
    }
  });

  // Depends on the configured field of view
  constexpr std::uint64_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::uint64_t expectedNumberOfSegments             = 1;

  sick::compact::scan_data::DataLossMonitor dataLossMonitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegments};

  sick::LRS4000::Driver driver(sensorAddress.address, sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver()                                         //
    .setup()                                                    //
    .setDataLossMonitor(std::move(dataLossMonitor), onDataLoss) //
    .setOnNewFrameCallback(onNewScanData);
  driver.run();
  std::this_thread::sleep_for(60s);
  deviceHealthThread.join();

  return 0;
}
