/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "ParameterBackupRestore.hpp"
#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

namespace {

// A challenge response body that also passes the header.status check.
constexpr char const* c_challengeResponse =
  R"({"header":{"status":0,"message":"Ok"},"challenge":{"realm":"realm","nonce":"nonce","opaque":"opaque","salt":[]}})";

// Session-token response returned by POST /api/CreateSessionToken.
constexpr char const* c_sessionTokenResponse = R"({"header":{"status":0,"message":"Ok"},"data":{"token":"sess-tok"}})";

class ParameterBackupRestoreTest : public ::testing::Test
{
protected:
  ParameterBackupRestoreTest()
    : m_http(std::make_shared<sick::test::TestHttpClient>())
    , m_client(m_http, sick::UserLevel::Service, "servicelevel")
  { }

  // Every backup/restore call first acquires a session token (challenge + CreateSessionToken).
  void queueSessionToken() const
  {
    m_http->queueJsonResponse(c_challengeResponse);
    m_http->queueJsonResponse(c_sessionTokenResponse);
  }

  std::shared_ptr<sick::test::TestHttpClient> m_http;
  sick::SopasClient m_client;
};

} // namespace

TEST_F(ParameterBackupRestoreTest, fetchFromSensor_with_existing_file_returns_its_bytes)
{
  queueSessionToken();
  m_http->queueResponse(200, "BACKUP-BYTES", "application/octet-stream");

  auto const backup = sick::parameters::backup::fetchFromSensor(m_client);

  EXPECT_EQ(backup, "BACKUP-BYTES");

  auto const& request = m_http->requests.back();
  EXPECT_EQ(request.method, sick::HttpMethod::Get);
  EXPECT_EQ(request.path, "/api/parameterbackup");
  ASSERT_EQ(request.headers.size(), 1U);
  EXPECT_EQ(request.headers[0].first, "X-Session-Token");
  EXPECT_EQ(request.headers[0].second, "sess-tok");
}

TEST_F(ParameterBackupRestoreTest, fetchFromSensor_with_error_status_throws)
{
  queueSessionToken();
  m_http->queueResponse(404, "");

  EXPECT_THROW(sick::parameters::backup::fetchFromSensor(m_client), std::runtime_error);
}

TEST_F(ParameterBackupRestoreTest, uploadToSensor_sends_octet_stream_put_with_session_header)
{
  queueSessionToken();
  m_http->queueResponse(200, "");

  sick::parameters::restore::uploadToSensor("RESTORE-CONTENT", m_client);

  auto const& request = m_http->requests.back();
  EXPECT_EQ(request.method, sick::HttpMethod::Put);
  EXPECT_EQ(request.path, "/api/parameterbackup");
  EXPECT_EQ(request.contentType, "application/octet-stream");
  EXPECT_EQ(request.body, "RESTORE-CONTENT");
  ASSERT_EQ(request.headers.size(), 1U);
  EXPECT_EQ(request.headers[0].second, "sess-tok");
}

TEST_F(ParameterBackupRestoreTest, uploadToSensor_with_error_status_throws)
{
  queueSessionToken();
  m_http->queueResponse(500, "");

  EXPECT_THROW(sick::parameters::restore::uploadToSensor("x", m_client), std::runtime_error);
}
