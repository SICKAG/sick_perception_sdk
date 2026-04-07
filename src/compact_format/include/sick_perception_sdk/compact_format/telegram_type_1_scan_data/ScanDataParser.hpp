/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <functional>
#include <vector>

namespace sick::compact::scan_data {

class SDK_EXPORT Parser : public CompactParser
{
public:
  using DataT = ScanData;

  /**
   * @throws std::invalid_argument if validation or parsing fails.
   */
  static auto validateAndParse(ByteView data, bool validateChecksum) -> DataT;

  auto getSize(ByteView data) const -> std::optional<std::size_t> override;

private:
  // The size of some of the fields in the compact binary data is different from the data structure.
  // Beam::azimuth is a float, but in the binary data it is a std::uint16_t.
  static constexpr std::size_t kSizeOfBinaryAzimuth = sizeof(std::uint16_t);
  // Echo::distance is a float, but in the binary data it is a std::uint16_t.
  static constexpr std::size_t kSizeOfBinaryDistance = sizeof(std::uint16_t);
  // Echo::intensity is a float, but in the binary data it is a std::uint16_t.
  static constexpr std::size_t kSizeOfBinaryIntensity = sizeof(std::uint16_t);
  // In the binary data the intensity value is between 0 and 65,535, in the data structure it is between 0.0 and 1.0.
  static constexpr float kIntensityScalingFactor = 65'535.0f;

  // The offset from the start of the module meta data of the numberOfRows field.
  static constexpr std::size_t kNumberOfRowsOffset =
    sizeof(Module::MetaData::segmentIndex) + sizeof(Module::MetaData::frameSequenceNumber) + sizeof(Module::MetaData::senderSerialNumber);

  // The number of bytes by which the module meta data grows per row in the module
  static constexpr std::size_t kModuleMetaDataSizePerRow = sizeof(Module::RowMetaData);

  /**
   * @brief Reads module meta data from the data.
   * @return The number of bytes read.
   * @throws std::invalid_argument if there is not enough data.
   */
  static auto readModuleMetaData(ByteView data, std::uint32_t version, Module::MetaData& metaData) -> std::size_t;

  /**
   * @brief Reads the beam data of a module from the data.
   * @return The number of bytes read.
   * @throws std::invalid_argument if there is not enough data.
   */
  static auto readModuleBeamData(ByteView data, Module::MetaData const& metaData, std::vector<Column>& columns) -> std::size_t;

  /**
   * @brief Reads a module (meta data and beams) from the data.
   * @return The number of bytes read.
   */
  static auto readModule(ByteView data, std::uint32_t version, Module& module) -> std::size_t;

  /**
   * @brief Gets the number of bytes of the next module.
   * @return The number of bytes of the next module, or std::nullopt if not enough data.
   */
  static auto getNumberOfBytesOfNextModule(ByteView data, std::uint32_t version) -> std::optional<std::uint32_t>;

  template <typename ValueT>
  static auto readRowMetaDataArray(
    ByteView data,
    std::size_t numberOfRows,
    std::vector<Module::RowMetaData>& rowMetaData,
    std::function<ValueT&(Module::RowMetaData&)> const& memberAccessor
  ) -> std::size_t
  {
    std::size_t numberOfBytesRead = 0;
    for (std::size_t i = 0; i < numberOfRows; ++i)
    {
      numberOfBytesRead += Parser::readValueUnsafe<ValueT>(data.subview(numberOfBytesRead), memberAccessor(rowMetaData[i]));
    }

    return numberOfBytesRead;
  }
};

} // namespace sick::compact::scan_data
