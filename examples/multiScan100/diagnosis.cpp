/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/multiScan100_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>

#include <chrono>
#include <iostream>
#include <thread>

using namespace sick::literals;
using namespace std::chrono_literals;
using LossCounts = sick::compact::scan_data::DataLossMonitor::LossCounts;

std::uint8_t numberOfScans = 0;

void onNewScanData(sick::compact::scan_data::ScanData const& data)
{
  numberOfScans++;
  if (numberOfScans == 100)
  {
    std::cout << "Received scan data with telegram sequence number: " << data.telegramHeader.telegramSequenceNumber << '\n';
    numberOfScans = 0;
  }
}

void onDataLoss(LossCounts const& lossCounts)
{
  std::cout << "Data losses detected: lost telegrams=" << lossCounts.numberOfLostTelegrams << ", lost frames=" << lossCounts.numberOfLostFrames
            << ", lost segments=" << lossCounts.numberOfLostSegments << '\n';
}

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  auto const deviceAddress = sick::examples::getDeviceAddress(argc, argv);

  sick::Log::init(sick::LogLevel::Info);

  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(deviceAddress, 80);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  sick::multiScan100::v2_4_2_0R::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  try
  {
    std::cout << "Diagnosis for device at " << configurator.sensorIPAddress.get().toString() << '\n';
    std::cout << "You can find a diagnosis overview at: http://" + configurator.sensorIPAddress.get().toString() + "/#/diagnosis/overview\n";
    std::cout << "DeviceType:      " << configurator.deviceType.get() << '\n';
    std::cout << "DeviceState:     " << static_cast<int>(configurator.deviceState.get()) << '\n';
    std::cout << "FirmwareVersion: " << configurator.firmwareVersion.get() << '\n';
    std::cout << "LocationName:    " << configurator.locationName.get() << '\n';
    std::cout << "OrderNumber:     " << configurator.orderNumber.get() << '\n';
    std::cout << "SerialNumber:    " << configurator.serialNumber.get() << '\n';
    std::cout << "SystemTime:      " << configurator.systemTime.get().count() << " us since epoch\n";
    std::cout << "SensorPosition:  " << configurator.sensorPosition.get().toString() << '\n';

    std::cout << "Blinking the device LEDs for identification...\n";
    configurator.findMe(5_s);

    std::cout << "Configuring scan data streaming...\n";
    configurator.enableScanDataStreaming("192.168.0.100", 2115); // Enter your computer's IP address
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
        std::cout << "DeviceState: " << static_cast<int>(configurator.deviceState.get()) << '\n';
        std::cout << "Temperature: " << configurator.sensorTemperature.get() << '\n';

        auto contaminationData = configurator.contaminationData.get();
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
        std::cout << "Polling error: " << exception.what() << '\n';
      }
      std::this_thread::sleep_for(2s);
    }
  });

  // depends on the configured field of view
  constexpr std::uint64_t expectedNumberOfSegments = 12;

  std::uint64_t const expectedFrameSequenceNumberIncrement =
    configurator.intervalFilter.isEnabled() ? static_cast<std::uint64_t>(configurator.intervalFilter.get().value()) : 1;

  sick::compact::scan_data::DataLossMonitor dataLossMonitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegments};

  sick::multiScan100::Driver driver(sick::examples::printExceptionMessage);
  driver
    .scanDataReceiver()                                         //
    .setup()                                                    //
    .setDataLossMonitor(std::move(dataLossMonitor), onDataLoss) //
    .setOnNewSegmentCallback(onNewScanData);
  driver.run();
  std::this_thread::sleep_for(60s);
  deviceHealthThread.join();

  return 0;
}
