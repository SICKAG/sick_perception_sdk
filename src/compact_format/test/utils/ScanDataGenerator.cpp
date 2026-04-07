/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "ScanDataGenerator.hpp"

namespace sick::test {

namespace {

static constexpr Angle kElevationResolution = Angle::fromDegrees(1.0f);
static constexpr Angle kAzimuthResolution   = Angle::fromDegrees(1.0f);

} // namespace

ScanDataGenerator::ScanDataGenerator()
  : m_frameSequenceNumber(0)
  , m_numberOfColumns(1)
  , m_numberOfEchoesPerBeam(1)
  , m_numberOfRows(1)
  , m_numberOfModules(1)
  , m_numberOfSegmentsPerFrame(1)
  , m_segmentIndex(0)
  , m_telegramSequenceNumber(0)
{ }

auto ScanDataGenerator::withNumberOfColumns(int value) -> ScanDataGenerator&
{
  m_numberOfColumns = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfEchoesPerBeam(int value) -> ScanDataGenerator&
{
  m_numberOfEchoesPerBeam = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfRows(int value) -> ScanDataGenerator&
{
  m_numberOfRows = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfSegmentsPerFrame(int value) -> ScanDataGenerator&
{
  m_numberOfSegmentsPerFrame = value;
  return *this;
}

auto ScanDataGenerator::withTelegramSequenceNumber(std::uint64_t value) -> ScanDataGenerator&
{
  m_telegramSequenceNumber = value;
  return *this;
}

auto ScanDataGenerator::next(Timestamp transmitTimestamp) -> compact::scan_data::ScanData
{
  constexpr std::uint32_t kStartOfFrame    = 0x02020202;
  constexpr std::uint32_t kTelegramVersion = 1;

  // Initialize the header structure
  compact::TelegramHeader header {
    kStartOfFrame,
    compact::TelegramType::ScanData,
    m_telegramSequenceNumber,
    transmitTimestamp,
    kTelegramVersion,
    0 // number of bytes of first module; we don't use this for tests
  };

  // Add the module data to the header
  std::vector<compact::scan_data::Module> modules;
  for (int i = 0; i < m_numberOfModules; ++i)
  {
    modules.push_back(createModule());
  }

  constexpr std::uint32_t kChecksum = 0; // We don't use this for tests

  compact::scan_data::ScanData data {header, std::move(modules), kChecksum};
  m_segmentIndex++;
  if (m_segmentIndex == m_numberOfSegmentsPerFrame)
  {
    m_segmentIndex = 0;
    m_frameSequenceNumber++;
  }
  m_telegramSequenceNumber++;
  return data;
}

void ScanDataGenerator::reset()
{
  m_telegramSequenceNumber = 0;
  m_segmentIndex           = 0;
  m_frameSequenceNumber    = 0;
}

auto ScanDataGenerator::createModule() -> compact::scan_data::Module
{
  // Start azimuth of the current segment
  auto const startAzimuth = kAzimuthResolution * m_segmentIndex * m_numberOfColumns;
  // End azimuth of the current segment
  auto const stopAzimuth = startAzimuth + kAzimuthResolution * (m_numberOfColumns - 1);
  // Timestamp of the first beam of the segment
  auto const firstTimestamp = Timestamp::fromMicrosecondsSinceEpoch(m_telegramSequenceNumber * 1'000);
  // Timestamp of the last beam of the segment
  auto const lastTimestamp = firstTimestamp + Duration::fromMicroseconds(m_numberOfColumns - 1);

  constexpr std::uint32_t kSenderId = 4242;

  using EchoContent = compact::scan_data::EchoContent;
  using BeamContent = compact::scan_data::BeamContent;

  compact::scan_data::Module::MetaData metaData = {
    m_segmentIndex,
    m_frameSequenceNumber,
    kSenderId,
    m_numberOfRows,
    m_numberOfColumns,
    m_numberOfEchoesPerBeam,
    std::vector<compact::scan_data::Module::RowMetaData>(m_numberOfRows),
    1.0f, // distanceScalingFactor
    0,    // numberOfBytesOfNextModule; we don't use this for tests
    BitField<EchoContent>(EchoContent::All),
    BitField<BeamContent>(BeamContent::None)
  };

  for (auto i = 0; i < m_numberOfRows; i++)
  {
    metaData.rowMetaData[i].firstBeamTimestamp = firstTimestamp;
    metaData.rowMetaData[i].lastBeamTimestamp  = lastTimestamp;
    metaData.rowMetaData[i].elevation          = kElevationResolution * i;
    metaData.rowMetaData[i].firstBeamAzimuth   = startAzimuth;
    metaData.rowMetaData[i].lastBeamAzimuth    = stopAzimuth;
  }

  std::vector<compact::scan_data::Column> columns;
  for (int column = 0; column < m_numberOfColumns; ++column)
  {
    compact::scan_data::Column columnData;
    for (int row = 0; row < m_numberOfRows; ++row)
    {
      std::vector<compact::scan_data::Echo> echoes;
      for (int echoIndex = 0; echoIndex < 1; ++echoIndex)
      {
        compact::scan_data::Echo echo;
        echo.distance = Distance::fromMeters(1.0f);
        echoes.push_back(echo);
      }

      compact::scan_data::Beam beam = {std::move(echoes), 0, startAzimuth + kAzimuthResolution * column};
      columnData.push_back(beam);
    }
    columns.push_back(columnData);
  }
  compact::scan_data::Module data {
    metaData,
    std::move(columns),
  };
  return data;
}

} // namespace sick::test
