/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <cstdint>
#include <string>
#include <vector>

namespace sick::test {

/**
 * @brief Read the contents of Compact data in binary file into a vector of bytes.
 * 
 * @param filePath Path to the binary file relative to the current working directory.
 */
auto readBinary(std::string const& relativeFilePath) -> std::vector<std::uint8_t>;

/**
 * @brief Recompute and update the CRC32 checksum at the end of the data vector.
 * 
 * This function uses production code from Crc32Utils.hpp to compute the checksum and
 * not an independent implementation of the CRC32 algorithm.
 * 
 * @param data Vector of bytes containing the Compact data. The last 4 bytes are replaced with the new checksum.
 */
void recomputeChecksum(std::vector<std::uint8_t>& data);

} // namespace sick::test
