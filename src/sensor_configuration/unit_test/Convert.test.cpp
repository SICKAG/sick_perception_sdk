/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Convert.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/LSPdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3/LSPsetdatetime.g.hpp>

#include <array>
#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>

namespace {

using PicoScan150LSPDateTime = sick::picoScan150::v2_3_3::api::rest::LSPdatetime::Get::Response::LSPdatetime;
using PicoScan150SetDateTime = sick::picoScan150::v2_3_3::api::rest::LSPsetdatetime::Post::Request::DateTime;

constexpr std::uint64_t kKnownUtcEpochMicroseconds = 1'709'210'096'123'456ULL;

TEST(ConvertTest, to_timestamp_with_picoscan150_lspdatetime_returns_expected_timestamp)
{
  PicoScan150LSPDateTime const payload {
    static_cast<std::uint16_t>(2024),
    static_cast<std::uint8_t>(2),
    static_cast<std::uint8_t>(29),
    static_cast<std::uint8_t>(12),
    static_cast<std::uint8_t>(34),
    static_cast<std::uint8_t>(56),
    static_cast<std::uint32_t>(123'456)
  };

  auto const timestamp = sick::convert::toTimestamp(payload);

  EXPECT_EQ(timestamp.microsecondsSinceEpoch(), kKnownUtcEpochMicroseconds);
}

TEST(ConvertTest, to_sopas_payload_with_timestamp_sets_expected_picoscan150_datetime_values)
{
  auto const timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(kKnownUtcEpochMicroseconds);

  auto const payload = sick::convert::toSopasPayload<PicoScan150SetDateTime>(timestamp);

  EXPECT_EQ(payload._uiYear.value(), 2024U);
  EXPECT_EQ(payload._usiMonth.value(), 2U);
  EXPECT_EQ(payload._usiDay.value(), 29U);
  EXPECT_EQ(payload._usiHour.value(), 12U);
  EXPECT_EQ(payload._usiMinute.value(), 34U);
  EXPECT_EQ(payload._usiSec.value(), 56U);
  EXPECT_EQ(payload._udiUSec.value(), 123'456U);
}

TEST(ConvertTest, round_trip_with_picoscan150_payload_types_sets_original_datetime_values)
{
  PicoScan150LSPDateTime const sourcePayload {
    static_cast<std::uint16_t>(2035),
    static_cast<std::uint8_t>(12),
    static_cast<std::uint8_t>(31),
    static_cast<std::uint8_t>(23),
    static_cast<std::uint8_t>(59),
    static_cast<std::uint8_t>(58),
    static_cast<std::uint32_t>(999'999)
  };

  auto const timestamp = sick::convert::toTimestamp(sourcePayload);
  auto const payload   = sick::convert::toSopasPayload<PicoScan150SetDateTime>(timestamp);

  EXPECT_EQ(payload._uiYear.value(), sourcePayload._uiYear.value());
  EXPECT_EQ(payload._usiMonth.value(), sourcePayload._usiMonth.value());
  EXPECT_EQ(payload._usiDay.value(), sourcePayload._usiDay.value());
  EXPECT_EQ(payload._usiHour.value(), sourcePayload._usiHour.value());
  EXPECT_EQ(payload._usiMinute.value(), sourcePayload._usiMinute.value());
  EXPECT_EQ(payload._usiSec.value(), sourcePayload._usiSec.value());
  EXPECT_EQ(payload._udiUSec.value(), sourcePayload._udiUSec.value());
}

} // namespace

