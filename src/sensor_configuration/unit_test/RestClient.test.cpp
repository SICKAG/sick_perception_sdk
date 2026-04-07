/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/sensor_configuration/RestClient/RestClient.hpp>

#include <gtest/gtest.h>

using namespace sick;

class RestClientTest : public ::testing::Test
{
protected:
  RestClientTest()
    : m_httpClient(std::make_shared<sick::test::TestHttpClient>())
    , m_restClient(m_httpClient)
  { }

  std::shared_ptr<sick::test::TestHttpClient> m_httpClient;
  RestClient m_restClient;
};

TEST_F(RestClientTest, get_with_single_parameter_calls_correct_endpoint)
{
  m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"DeviceType":"TestDevice"}})");

  auto const result = m_restClient.get<std::string>("DeviceType");

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", m_httpClient->requestedGetEndpoints[0]);
  EXPECT_EQ("TestDevice", result);
}

TEST_F(RestClientTest, get_with_two_parameters_and_data_field_deserializes_correctly)
{
  m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"SomeField":"TestValue"}})");

  auto const result = m_restClient.get<std::string>("SomeVariable", "SomeField", true);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/SomeVariable", m_httpClient->requestedGetEndpoints[0]);
  EXPECT_EQ("TestValue", result);
}

TEST_F(RestClientTest, get_without_data_field_deserializes_correctly)
{
  m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"SomeField":"TestValue"})");

  auto const result = m_restClient.get<std::string>("SomeVariable", "SomeField", false);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/SomeVariable", m_httpClient->requestedGetEndpoints[0]);
  EXPECT_EQ("TestValue", result);
}

TEST_F(RestClientTest, get_throws_when_header_status_is_not_zero)
{
  m_httpClient->getResponses.push_back(R"({"header":{"status":404,"message":"Not Found"}})");

  EXPECT_THROW(m_restClient.get<std::string>("DeviceType"), std::runtime_error);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", m_httpClient->requestedGetEndpoints[0]);
}

TEST_F(RestClientTest, get_throws_when_response_has_invalid_structure)
{
  // Missing the expected field in data
  m_httpClient->getResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"WrongField":"TestValue"}})");

  EXPECT_THROW(m_restClient.get<std::string>("DeviceType"), std::exception);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", m_httpClient->requestedGetEndpoints[0]);
}

TEST_F(RestClientTest, get_error_message_is_included_in_exception)
{
  m_httpClient->getResponses.push_back(R"({"header":{"status":500,"message":"Internal Server Error"}})");

  try
  {
    m_restClient.get<std::string>("DeviceType");
    FAIL() << "Expected std::runtime_error to be thrown";
  }
  catch (std::runtime_error const& exception)
  {
    EXPECT_NE(std::string(exception.what()).find("Internal Server Error"), std::string::npos);
  }
  catch (...)
  {
    FAIL() << "Expected std::runtime_error, got different exception type";
  }
}

TEST_F(RestClientTest, get_throws_when_response_is_empty_json_object)
{
  m_httpClient->getResponses.push_back(R"({})");

  EXPECT_THROW(m_restClient.get<std::string>("DeviceType"), std::exception);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", m_httpClient->requestedGetEndpoints[0]);
}

TEST_F(RestClientTest, get_throws_when_response_is_empty_json_string)
{
  m_httpClient->getResponses.push_back(R"("")");

  EXPECT_THROW(m_restClient.get<std::string>("DeviceType"), std::exception);

  ASSERT_EQ(1, m_httpClient->requestedGetEndpoints.size());
  EXPECT_EQ("/api/DeviceType", m_httpClient->requestedGetEndpoints[0]);
}

TEST_F(RestClientTest, post_with_payload_sends_correct_request)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  m_restClient.post("TestVariable").withoutAuthentication().withPlainRequestPayload(42).execute();

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  EXPECT_EQ(R"({"data":42})", m_httpClient->requestedPostPayloads[0]);
}

// Detailed tests for PostRequest are in PostRequest.test.cpp.
