/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils.hpp"

#include "test_config.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace sick::test {

auto readBinary(std::string const& relativeFilePath) -> std::vector<std::uint8_t>
{
  auto absoluteFilePath = std::filesystem::absolute(getExecutablePath() / relativeFilePath);
  std::ifstream file(absoluteFilePath, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Could not open file: " + absoluteFilePath.string());
  }

  std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return data;
}

void recomputeChecksum(std::vector<std::uint8_t>& data)
{
  auto const checksum = sick::compact::crc32(ByteView {data}.first(data.size() - sizeof(std::uint32_t)));
  std::copy(
    reinterpret_cast<std::uint8_t const*>(&checksum),
    reinterpret_cast<std::uint8_t const*>(&checksum) + sizeof(std::uint32_t),
    data.end() - sizeof(std::uint32_t)
  );
}

} // namespace sick::test
