/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/loadBinaryFile.hpp>

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace sick {

auto loadBinaryFile(std::string const& path) -> std::vector<std::uint8_t>
{
  std::ifstream file(path, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Failed to open file: " + path);
  }

  file.seekg(0, std::ios::end);
  auto const fileSize = file.tellg();
  if (fileSize < 0)
  {
    throw std::runtime_error("Failed to determine size of file: " + path);
  }
  file.seekg(0, std::ios::beg);

  std::vector<std::uint8_t> data;
  data.reserve(static_cast<std::size_t>(fileSize));
  data.insert(data.begin(), std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
  return data;
}

} // namespace sick
