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

auto ScanDataGenerator::withNumberOfColumns(std::size_t value) -> ScanDataGenerator&
{
  m_numberOfColumns = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfEchoesPerBeam(std::size_t value) -> ScanDataGenerator&
{
  m_numberOfEchoesPerBeam = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfRows(std::size_t value) -> ScanDataGenerator&
{
  m_numberOfRows = value;
  return *this;
}

auto ScanDataGenerator::withNumberOfSegmentsPerFrame(std::size_t value) -> ScanDataGenerator&
{
  m_numberOfSegmentsPerFrame = value;
  return *this;
}

auto ScanDataGenerator::withTelegramSequenceNumber(std::size_t value) -> ScanDataGenerator&
{
  m_telegramSequenceNumber = value;
  return *this;
}

auto ScanDataGenerator::next(Timestamp transmitTimestamp) -> compact::scan_data::ScanData
{
  constexpr std::uint32_t kSenderSerialNumber = 42;

  // Initialize the header structure
  compact::TelegramHeader header {m_telegramSequenceNumber, transmitTimestamp, kSenderSerialNumber};

  // Add the module data to the header
  std::vector<compact::scan_data::Module> modules;
  for (std::size_t i = 0; i < m_numberOfModules; ++i)
  {
    modules.push_back(createModule());
  }

  constexpr std::uint32_t kChecksum = 0; // We don't use this for tests

  compact::scan_data::ScanData data {header, m_frameSequenceNumber, m_segmentIndex, std::move(modules)};
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

  std::vector<compact::scan_data::Module::RowMetaData> rowsMetaData;
  for (std::size_t i = 0; i < m_numberOfRows; i++)
  {
    compact::scan_data::Module::RowMetaData rowMetaData;
    rowMetaData.firstBeamTimestamp = firstTimestamp;
    rowMetaData.lastBeamTimestamp  = lastTimestamp;
    rowMetaData.elevation          = kElevationResolution * i;
    rowMetaData.firstBeamAzimuth   = startAzimuth;
    rowMetaData.lastBeamAzimuth    = stopAzimuth;
    rowsMetaData.push_back(rowMetaData);
  }

  auto const numberOfBeams   = static_cast<std::size_t>(m_numberOfColumns) * static_cast<std::size_t>(m_numberOfRows);
  auto const numberOfSamples = numberOfBeams * static_cast<std::size_t>(m_numberOfEchoesPerBeam);

  // Create flat arrays for the linear data layout
  std::vector<Distance> distances(numberOfSamples, Distance::fromMeters(1.0f));
  std::vector<float> intensities(numberOfSamples, 0.0f);
  std::vector<BitField<compact::scan_data::BeamProperties>> beamProperties; // Empty since BeamContent is None
  std::vector<Angle> beamAzimuths;                                          // Empty since BeamContent is None

  compact::scan_data::Module data {
    m_numberOfColumns,
    m_numberOfEchoesPerBeam,
    rowsMetaData,
    std::move(distances),
    std::move(intensities),
    std::move(beamProperties),
    std::move(beamAzimuths),
  };

  for (std::size_t i = 0; i < m_numberOfRows; i++)
  {
    data.rowMetaData[i].firstBeamTimestamp = firstTimestamp;
    data.rowMetaData[i].lastBeamTimestamp  = lastTimestamp;
    data.rowMetaData[i].elevation          = kElevationResolution * i;
    data.rowMetaData[i].firstBeamAzimuth   = startAzimuth;
    data.rowMetaData[i].lastBeamAzimuth    = stopAzimuth;
  }

  return data;
}

} // namespace sick::test
