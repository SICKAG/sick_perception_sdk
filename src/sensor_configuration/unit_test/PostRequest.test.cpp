/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/sensor_configuration/RestClient/PostRequest.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>

#include <gtest/gtest.h>

using namespace sick;
using namespace std::string_literals;

class PostRequestTest : public ::testing::Test
{
protected:
  PostRequestTest()
    : m_httpClient(std::make_shared<sick::test::TestHttpClient>())
  { }

  std::shared_ptr<sick::test::TestHttpClient> m_httpClient;
};

TEST_F(PostRequestTest, execute_without_authentication_or_payload_sends_empty_json)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withoutRequestPayload().execute();

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  EXPECT_EQ("null", m_httpClient->requestedPostPayloads[0]);
}

TEST_F(PostRequestTest, execute_with_plain_request_payload_sends_correct_json)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withPlainRequestPayload(42).execute();

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  EXPECT_EQ(R"({"data":42})", m_httpClient->requestedPostPayloads[0]);
}

TEST_F(PostRequestTest, execute_with_field_request_payload_sends_correct_json)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withRequestPayload("SomeField", "TestValue").execute();

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  EXPECT_EQ(R"({"data":{"SomeField":"TestValue"}})", m_httpClient->requestedPostPayloads[0]);
}

TEST_F(PostRequestTest, execute_with_authentication_includes_header_in_payload)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  AuthenticationHeader authHeader;
  authHeader.user     = "testuser";
  authHeader.nonce    = "testnonce";
  authHeader.realm    = "testrealm";
  authHeader.response = "testresponse";
  authHeader.opaque   = "testopaque";

  PostRequest request("TestVariable", m_httpClient);
  request.withAuthentication(authHeader).withoutRequestPayload().execute();

  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  auto const& payload = m_httpClient->requestedPostPayloads[0];

  // Verify that authentication header is included
  EXPECT_NE(payload.find(R"("header")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("user":"testuser")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("nonce":"testnonce")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("realm":"testrealm")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("response":"testresponse")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("opaque":"testopaque")"s), std::string::npos);
}

TEST_F(PostRequestTest, execute_with_authentication_and_payload_merges_both)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  AuthenticationHeader authHeader;
  authHeader.user = "testuser";

  PostRequest request("TestVariable", m_httpClient);
  request.withAuthentication(authHeader).withRequestPayload("Field", "Value").execute();

  ASSERT_EQ(1, m_httpClient->requestedPostPayloads.size());
  auto const& payload = m_httpClient->requestedPostPayloads[0];

  // Verify both header and data are present
  EXPECT_NE(payload.find(R"("header")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("user":"testuser")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("data")"s), std::string::npos);
  EXPECT_NE(payload.find(R"("Field":"Value")"s), std::string::npos);

  // Verify header comes before data (order matters for SOPAS REST API)
  auto headerPos = payload.find(R"("header")"s);
  auto dataPos   = payload.find(R"("data")"s);
  EXPECT_LT(headerPos, dataPos);
}

TEST_F(PostRequestTest, execute_throws_when_response_status_is_not_zero)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":403,"message":"Forbidden"}})");

  PostRequest request("TestVariable", m_httpClient);

  EXPECT_THROW(request.withoutAuthentication().withoutRequestPayload().execute(), std::runtime_error);

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
}

TEST_F(PostRequestTest, execute_error_message_includes_status_code_and_message)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":500,"message":"Internal Server Error"}})");

  PostRequest request("TestVariable", m_httpClient);

  try
  {
    request.withoutAuthentication().withoutRequestPayload().execute();
    FAIL() << "Expected std::runtime_error to be thrown";
  }
  catch (std::runtime_error const& exception)
  {
    auto const message = std::string(exception.what());
    EXPECT_NE(message.find("500"s), std::string::npos);
    EXPECT_NE(message.find("Internal Server Error"s), std::string::npos);
  }
  catch (...)
  {
    FAIL() << "Expected std::runtime_error, got different exception type";
  }
}

TEST_F(PostRequestTest, withResponsePayloadInData_deserializes_correctly)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"Result":"Success"}})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withoutRequestPayload().execute();

  auto const result = request.withResponsePayloadInData<std::string>("Result");

  EXPECT_EQ("Success", result);
}

TEST_F(PostRequestTest, withPlainResponsePayload_with_field_name_deserializes_correctly)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"Result":"Success"})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withoutRequestPayload().execute();

  auto const result = request.withPlainResponsePayload<std::string>("Result");

  EXPECT_EQ("Success", result);
}

TEST_F(PostRequestTest, withPlainResponsePayload_without_field_name_deserializes_correctly)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":"DirectValue"})");

  PostRequest request("TestVariable", m_httpClient);
  request.withoutAuthentication().withoutRequestPayload().execute();

  auto const result = request.withPlainResponsePayload<std::string>();

  EXPECT_EQ("DirectValue", result);
}

TEST_F(PostRequestTest, method_chaining_works_correctly)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"},"data":{"Result":true}})");

  // Test that the entire chain works in one expression
  auto const result =
    PostRequest("TestVariable", m_httpClient) //
      .withoutAuthentication()                //
      .withRequestPayload("Input", 123)       //
      .execute()                              //
      .withResponsePayloadInData<bool>("Result");

  EXPECT_TRUE(result);
  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/TestVariable", m_httpClient->requestedPostEndpoints[0]);
}

TEST_F(PostRequestTest, execute_uses_correct_endpoint_format)
{
  m_httpClient->postResponses.push_back(R"({"header":{"status":0,"message":"Ok"}})");

  PostRequest request("MyCustomVariable", m_httpClient);
  request.withoutAuthentication().withoutRequestPayload().execute();

  ASSERT_EQ(1, m_httpClient->requestedPostEndpoints.size());
  EXPECT_EQ("/api/MyCustomVariable", m_httpClient->requestedPostEndpoints[0]);
}
