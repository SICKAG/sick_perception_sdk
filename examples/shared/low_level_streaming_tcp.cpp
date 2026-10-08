/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/socket/TcpClientSocket.hpp>
#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>

#if defined(USE_MULTISCAN200)
#  include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>
#else // Default to LRS4000
#  include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#endif

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  auto const sensorAddress = sick::examples::getSensorAddress("Low-level TCP streaming example", argc, argv);

  // Create a buffer to receive data. This will be reused for each receive call.
  std::vector<std::uint8_t> buffer(4'000'000);

  sick::TcpClientSocket socket {sensorAddress.address, 2115}; // Port is hard-coded in the sensor.
  socket.connect();

  sick::compact::StreamExtractor extractor;

  auto const startTime       = std::chrono::steady_clock::now();
  constexpr auto maxDuration = 10s;

  while (std::chrono::steady_clock::now() - startTime < maxDuration)
  {
    // Receive new data from the socket
    auto const numberOfReceivedBytes = socket.receive(buffer);
    if (numberOfReceivedBytes == 0)
    {
      continue;
    }

    // Extract telegrams from the received data. The extractor will collect data if the buffer contains partial Compact telegrams.
    auto const telegrams = extractor.extractTelegrams(sick::ByteView {buffer.data(), numberOfReceivedBytes});
    if (telegrams.empty())
    {
      continue;
    }

    // Here we parse only the first telegram for demonstration purposes.
    try
    {
#if defined(USE_MULTISCAN200)
      auto const data = sick::compact::multiscan200::Parser::validateAndParse(telegrams[0], true);
      std::cout << "Received data with size " << data.segmentMetaData.numberOfColumnsInSegment << " x " << data.segmentMetaData.numberOfRows << ".\n";
#else // LRS4000
      auto const scanData = sick::compact::scan_data::Parser::validateAndParse(telegrams[0], true);
      std::cout << "Received scan data with " << scanData.modules.size() << " modules.\n";
#endif
    }
    catch (std::exception const& exception)
    {
      std::cerr << "Failed to parse data: " << exception.what() << '\n';
    }
  }

  return 0;
}
