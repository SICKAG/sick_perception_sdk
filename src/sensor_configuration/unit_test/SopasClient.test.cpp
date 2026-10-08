/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/sensor_configuration/SopasClientImpl.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

namespace {

// A challenge response body that also passes the header.status check.
constexpr char const* c_challengeResponse =
  R"({"header":{"status":0,"message":"Ok"},"challenge":{"realm":"realm","nonce":"nonce","opaque":"opaque","salt":[]}})";

// Minimal SOPAS variable endpoint (Class 1 / Class 2), modelled on the generated payload contract.
struct DeviceTypeVar
{
  static constexpr char const* variableName = "DeviceType";
  static constexpr bool isSopasMethod       = false;

  struct Get
  {
    using Response = std::string;
  };

  struct Post
  {
    using Request = std::string;
  };
};

// SOPAS method endpoint (Class 3) with request and response payloads.
struct EchoMethod
{
  static constexpr char const* methodName = "Echo";
  static constexpr bool isSopasMethod     = true;

  struct Post
  {
    using Request  = int;
    using Response = int;
  };
};

// SOPAS method endpoint (Class 3) without request or response payloads.
struct RebootMethod
{
  static constexpr char const* methodName = "Reboot";
  static constexpr bool isSopasMethod     = true;

  struct Post
  {
    using Request  = void;
    using Response = void;
  };
};

// SOPAS method endpoint (Class 3) with a request but no response payload.
struct SetValueMethod
{
  static constexpr char const* methodName = "SetValue";
  static constexpr bool isSopasMethod     = true;

  struct Post
  {
    using Request  = int;
    using Response = void;
  };
};

// SOPAS method endpoint (Class 3) with no request but a response payload.
struct GetValueMethod
{
  static constexpr char const* methodName = "GetValue";
  static constexpr bool isSopasMethod     = true;

  struct Post
  {
    using Request  = void;
    using Response = int;
  };
};

class SopasClientTest : public ::testing::Test
{
protected:
  SopasClientTest()
    : m_http(std::make_shared<sick::test::TestHttpClient>())
    , m_client(m_http, sick::UserLevel::Service, "servicelevel")
  { }

  std::shared_ptr<sick::test::TestHttpClient> m_http;
  sick::SopasClient m_client;
};

} // namespace

TEST_F(SopasClientTest, readVariable_unwraps_data_field)
{
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"},"data":{"DeviceType":"someDevice"}})");

  auto const deviceType = m_client.readVariable<DeviceTypeVar>();

  EXPECT_EQ(deviceType, "someDevice");
  ASSERT_EQ(m_http->requests.size(), 1U);
  EXPECT_EQ(m_http->requests[0].method, sick::HttpMethod::Get);
  EXPECT_EQ(m_http->requests[0].path, "/api/DeviceType");
}

TEST_F(SopasClientTest, readVariable_throws_when_status_is_not_zero)
{
  m_http->queueJsonResponse(R"({"header":{"status":5,"message":"Not Found"}})");

  EXPECT_THROW(m_client.readVariable<DeviceTypeVar>(), std::runtime_error);
}

TEST_F(SopasClientTest, readVariable_throws_when_field_is_missing)
{
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"},"data":{"WrongField":"x"}})");

  EXPECT_THROW(m_client.readVariable<DeviceTypeVar>(), std::exception);
}

TEST_F(SopasClientTest, writeVariable_authenticates_then_wraps_payload)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"}})");

  m_client.writeVariable<DeviceTypeVar>("newValue");

  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[0].method, sick::HttpMethod::Post);
  EXPECT_EQ(m_http->requests[0].path, "/api/getChallenge");
  EXPECT_EQ(m_http->requests[1].method, sick::HttpMethod::Post);
  EXPECT_EQ(m_http->requests[1].path, "/api/DeviceType");

  auto const body = nlohmann::json::parse(m_http->requests[1].body);
  EXPECT_EQ(body.at("data").at("DeviceType").get<std::string>(), "newValue");
  ASSERT_TRUE(body.contains("header"));
  EXPECT_EQ(body.at("header").at("user").get<std::string>(), "Service");
  EXPECT_FALSE(body.at("header").at("response").get<std::string>().empty());
}

TEST_F(SopasClientTest, invokeMethod_places_payload_flat_and_unwraps_response)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"},"data":7})");

  auto const result = m_client.invokeMethod<EchoMethod>(5);

  EXPECT_EQ(result, 7);
  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[1].path, "/api/Echo");

  auto const body = nlohmann::json::parse(m_http->requests[1].body);
  EXPECT_EQ(body.at("data").get<int>(), 5);
}

TEST_F(SopasClientTest, invokeMethodWithoutRequestAndResponse_sends_only_header)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"}})");

  m_client.invokeMethodWithoutRequestAndResponse<RebootMethod>();

  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[1].path, "/api/Reboot");

  auto const body = nlohmann::json::parse(m_http->requests[1].body);
  EXPECT_TRUE(body.contains("header"));
  EXPECT_FALSE(body.contains("data"));
}

TEST_F(SopasClientTest, invokeMethod_throws_when_status_is_not_zero)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":3,"message":"Rejected"}})");

  EXPECT_THROW(m_client.invokeMethod<EchoMethod>(5), std::runtime_error);
}

TEST_F(SopasClientTest, invokeMethodWithoutResponse_sends_payload_flat)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"}})");

  m_client.invokeMethodWithoutResponse<SetValueMethod>(42);

  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[1].path, "/api/SetValue");

  auto const body = nlohmann::json::parse(m_http->requests[1].body);
  EXPECT_EQ(body.at("data").get<int>(), 42);
}

TEST_F(SopasClientTest, invokeMethodWithoutRequest_unwraps_response)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"},"data":9})");

  auto const result = m_client.invokeMethodWithoutRequest<GetValueMethod>();

  EXPECT_EQ(result, 9);
  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[1].path, "/api/GetValue");

  auto const body = nlohmann::json::parse(m_http->requests[1].body);
  EXPECT_TRUE(body.contains("header"));
  EXPECT_FALSE(body.contains("data"));
}

TEST_F(SopasClientTest, authenticate_reflects_challenge_and_produces_hex_response)
{
  m_http->queueJsonResponse(c_challengeResponse);

  auto const header = m_client.authenticate("SomeEndpoint");

  EXPECT_EQ(header.nonce, "nonce");
  EXPECT_EQ(header.opaque, "opaque");
  EXPECT_EQ(header.realm, "realm");
  EXPECT_EQ(header.user, "Service");
  EXPECT_EQ(header.response.size(), 64U); // SHA-256 hex digest length.
}

TEST_F(SopasClientTest, createSessionToken_returns_token_from_data)
{
  m_http->queueJsonResponse(c_challengeResponse);
  m_http->queueJsonResponse(R"({"header":{"status":0,"message":"Ok"},"data":{"token":"abc123"}})");

  auto const token = m_client.createSessionToken();

  EXPECT_EQ(token, "abc123");
  ASSERT_EQ(m_http->requests.size(), 2U);
  EXPECT_EQ(m_http->requests[1].path, "/api/CreateSessionToken");
}

TEST_F(SopasClientTest, sendRaw_forwards_request_without_envelope_handling)
{
  m_http->queueResponse(200, "raw-body", "application/octet-stream");

  sick::HttpRequest request;
  request.method = sick::HttpMethod::Get;
  request.path   = "/api/custom";

  auto const response = m_client.sendRaw(request);

  EXPECT_EQ(response.body, "raw-body");
  ASSERT_EQ(m_http->requests.size(), 1U);
  EXPECT_EQ(m_http->requests[0].path, "/api/custom");
}
