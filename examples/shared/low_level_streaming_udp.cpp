/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/socket/UdpListeningSocket.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();
  // Create a buffer to receive data. This will be reused for each receive call.
  std::vector<std::uint8_t> buffer(65'535);
  sick::UdpListeningSocket socket {2115}; // Listen on port 2115 for UDP packets (format Compact)

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

    try
    {
      // The UDP packets always contain one complete Compact telegram so we parse each packet into `ScanData`.
      auto const scanData = sick::compact::scan_data::Parser::validateAndParse(sick::ByteView {buffer.data(), numberOfReceivedBytes}, true);
      std::cout << "Received scan data with " << scanData.modules.size() << " modules.\n";
    }
    catch (std::exception const& exception)
    {
      std::cerr << "Failed to parse scan data: " << exception.what() << '\n';
    }
  }

  return 0;
}
