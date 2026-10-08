/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>

#include <cstdint>
#include <gtest/gtest.h>
#include <memory>

namespace {

// Verifies the thin glue the configurator adds on top of the generated endpoints: getSystemTimeOfSensor()
// reads /api/LSPdatetime and converts the broken-down device date/time into a Timestamp.
TEST(PicoScan150ConfiguratorGlueTest, get_system_time_of_sensor_reads_and_converts_device_datetime)
{
  auto httpClient = std::make_shared<sick::test::TestHttpClient>();
  httpClient->queueJsonResponse(
    R"({"header":{"status":0,"message":"Ok"},"data":{"LSPdatetime":{"uiYear":2024,"usiMonth":1,"usiDay":2,"usiHour":3,"usiMinute":4,"usiSec":5,"udiUSec":6}}})"
  );

  sick::picoScan150::v2_3_3::Configurator const configurator {httpClient, sick::UserLevel::Service, "servicelevel"};

  auto const timestamp = configurator.getSystemTimeOfSensor();

  // timegm(2024-01-02T03:04:05Z) == 1704164645 seconds since the Unix epoch, plus 6 microseconds.
  constexpr sick::Timestamp::value_type expectedSeconds       = 1704164645ULL;
  constexpr sick::Timestamp::value_type microsecondsPerSecond = 1000000ULL;
  EXPECT_EQ(timestamp.microsecondsSinceEpoch(), expectedSeconds * microsecondsPerSecond + 6ULL);

  ASSERT_EQ(httpClient->requests.size(), 1U);
  EXPECT_EQ(httpClient->requests[0].method, sick::HttpMethod::Get);
  EXPECT_EQ(httpClient->requests[0].path, "/api/LSPdatetime");
}

} // namespace
