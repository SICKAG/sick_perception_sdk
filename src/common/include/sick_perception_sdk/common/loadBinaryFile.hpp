/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace sick {

/**
 * @brief Read the entire contents of a file into a byte buffer.
 *
 * @param path Path to the file to read.
 * @return The file contents. An empty file yields an empty buffer.
 * @throws std::runtime_error if the file cannot be opened or its size cannot be determined.
 */
SDK_EXPORT auto loadBinaryFile(std::string const& path) -> std::vector<std::uint8_t>;

} // namespace sick
