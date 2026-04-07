/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
#include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>

#include <deque>
#include <gtest/gtest.h>
#include <vector>

using namespace sick::literals;
using namespace std::chrono_literals;

template <class ConfiguratorT>
class SensorConfiguratorTest : public ::testing::Test
{
protected:
  SensorConfiguratorTest()
    : m_httpClient(std::make_shared<sick::test::TestHttpClient>())
    , m_configurator {m_httpClient, sick::UserLevel::Service, "servicelevel"}
  { }

  std::shared_ptr<sick::test::TestHttpClient> m_httpClient;
  ConfiguratorT m_configurator;
};

using ConfiguratorTypes = ::testing::Types<sick::multiScan100::v2_4_2_0R::Configurator, sick::picoScan150::v2_2_1_0R::Configurator>;
TYPED_TEST_SUITE(SensorConfiguratorTest, ConfiguratorTypes);

TYPED_TEST(SensorConfiguratorTest, reading_variable_works_with_successful_response)
{
  this->m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"DeviceType":"someDevice"}})");
  auto const deviceType = this->m_configurator.deviceType.get();
  ASSERT_EQ(1, this->m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", this->m_httpClient->requestedGetEndpoints[0]);
  EXPECT_EQ(deviceType, "someDevice");
}

TYPED_TEST(SensorConfiguratorTest, reading_variable_throws_when_incorrect_data_in_response)
{
  // "TypeDevice" instead of "DeviceType" is invalid response content.
  this->m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"TypeDevice":"someDevice"}})");
  // The exception is most likely thrown by the JSON library but it is still good to test that the code fails in a predictable way.
  EXPECT_THROW(this->m_configurator.deviceType.get(), std::exception);
  ASSERT_EQ(1, this->m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", this->m_httpClient->requestedGetEndpoints[0]);
}

TYPED_TEST(SensorConfiguratorTest, reading_variable_throws_when_response_indicates_error)
{
  this->m_httpClient->getResponses.push_back(R"({"header":{"status":5,"message":"Not Found"}})");
  EXPECT_THROW(this->m_configurator.deviceType.get(), std::exception);
  ASSERT_EQ(1, this->m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", this->m_httpClient->requestedGetEndpoints[0]);
}
