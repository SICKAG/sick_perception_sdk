/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

auto getBenchmarkExecutablePath() -> std::filesystem::path;

namespace sick::benchmark {

static auto readBinary(std::string const& relativeFilePath) -> std::vector<std::uint8_t>
{
  auto absoluteFilePath = std::filesystem::absolute(getBenchmarkExecutablePath() / relativeFilePath);
  std::ifstream file(absoluteFilePath, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Could not open file: " + absoluteFilePath.string());
  }

  std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return data;
}

} // namespace sick::benchmark
