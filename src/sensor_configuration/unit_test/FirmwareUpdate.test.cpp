/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "FirmwareUpdate.hpp"
#include "test_utils/TestHttpClient.hpp"
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <chrono>
#include <cstdint>
#include <deque>
#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

enum class FakeUpdateState
{
  Initial,
  Busy,
  Error,
  Finished,
};

// Mirrors the nested contract that firmware_update::run expects from its UpdateStateRequestT.
struct FakeUpdateStateRequest
{
  struct Get
  {
    struct Response
    {
      using UpdateState = FakeUpdateState;
    };
  };
};

// Minimal stand-in for the generated Endpoints: records interactions and returns scripted states.
struct FakeEndpoints
{
  mutable int runFirmwareUpdateCalls = 0;
  mutable int getUpdateStateCalls    = 0;
  mutable std::deque<FakeUpdateState> scriptedStates;

  void runFirmwareUpdate() const
  {
    ++runFirmwareUpdateCalls;
  }

  auto getUpdateState() const -> FakeUpdateState
  {
    ++getUpdateStateCalls;
    if (scriptedStates.empty())
    {
      return FakeUpdateState::Busy;
    }
    auto const state = scriptedStates.front();
    scriptedStates.pop_front();
    return state;
  }
};

auto bytes(std::string const& content) -> std::vector<std::uint8_t>
{
  return {content.begin(), content.end()};
}

class FirmwareUpdateTest : public ::testing::Test
{
protected:
  FirmwareUpdateTest()
    : m_http(std::make_shared<sick::test::TestHttpClient>())
    , m_client(m_http, sick::UserLevel::Service, "servicelevel")
  {
    // Virtual clock: now() reads the accumulated time, wait() advances it. No real sleeping happens.
    m_time.now = [this] {
      return sick::Timestamp {} + sick::Duration::fromMilliseconds(static_cast<double>(m_elapsed.count()));
    };
    m_time.wait = [this](std::chrono::milliseconds duration) {
      m_elapsed += duration;
    };
    m_time.pollInterval = std::chrono::milliseconds {10};
  }

  // The upload path performs createSessionToken() (challenge + token) followed by the PUT upload.
  void queueSuccessfulUpload() const
  {
    m_http->queueJsonResponse(c_challengeResponse);
    m_http->queueJsonResponse(c_sessionTokenResponse);
    m_http->queueResponse(200, "");
  }

  template <class Timeout>
  void run(FakeEndpoints const& endpoints, std::vector<std::uint8_t> const& firmwareData, Timeout timeout) const
  {
    sick::firmware_update::run<FakeEndpoints, FakeUpdateStateRequest>(firmwareData, m_client, endpoints, timeout, m_time);
  }

  static constexpr char const* c_challengeResponse =
    R"({"header":{"status":0,"message":"Ok"},"challenge":{"realm":"realm","nonce":"nonce","opaque":"opaque","salt":[]}})";
  static constexpr char const* c_sessionTokenResponse = R"({"header":{"status":0,"message":"Ok"},"data":{"token":"sess-tok"}})";

  std::shared_ptr<sick::test::TestHttpClient> m_http;
  sick::SopasClient m_client;
  sick::firmware_update::TimeProvider m_time;
  std::chrono::milliseconds m_elapsed {0};
};

} // namespace

TEST_F(FirmwareUpdateTest, run_with_empty_firmware_throws)
{
  FakeEndpoints endpoints;

  EXPECT_THROW(run(endpoints, std::vector<std::uint8_t> {}, std::optional<sick::Duration> {}), std::runtime_error);
  EXPECT_EQ(endpoints.runFirmwareUpdateCalls, 0);
}

TEST_F(FirmwareUpdateTest, run_without_timeout_triggers_update_without_polling)
{
  queueSuccessfulUpload();
  FakeEndpoints endpoints;

  run(endpoints, bytes("firmware-bytes"), std::optional<sick::Duration> {});

  EXPECT_EQ(endpoints.runFirmwareUpdateCalls, 1);
  EXPECT_EQ(endpoints.getUpdateStateCalls, 0);

  auto const& upload = m_http->requests.back();
  EXPECT_EQ(upload.method, sick::HttpMethod::Put);
  EXPECT_EQ(upload.path, "/api/update");
  EXPECT_EQ(upload.contentType, "application/octet-stream");
  EXPECT_EQ(upload.body, "firmware-bytes");
}

TEST_F(FirmwareUpdateTest, run_with_timeout_polls_until_finished)
{
  queueSuccessfulUpload();
  FakeEndpoints endpoints;
  endpoints.scriptedStates = {FakeUpdateState::Busy, FakeUpdateState::Busy, FakeUpdateState::Finished};

  run(endpoints, bytes("fw"), std::optional<sick::Duration> {sick::Duration::fromSeconds(10)});

  EXPECT_EQ(endpoints.runFirmwareUpdateCalls, 1);
  EXPECT_EQ(endpoints.getUpdateStateCalls, 3);
}

TEST_F(FirmwareUpdateTest, run_with_error_state_throws)
{
  queueSuccessfulUpload();
  FakeEndpoints endpoints;
  endpoints.scriptedStates = {FakeUpdateState::Error};

  EXPECT_THROW(run(endpoints, bytes("fw"), std::optional<sick::Duration> {sick::Duration::fromSeconds(10)}), std::runtime_error);
}

TEST_F(FirmwareUpdateTest, run_with_unfinished_update_throws_on_timeout)
{
  queueSuccessfulUpload();
  FakeEndpoints endpoints; // no scripted states -> always Busy
  m_time.pollInterval = std::chrono::milliseconds {20};

  EXPECT_THROW(run(endpoints, bytes("fw"), std::optional<sick::Duration> {sick::Duration::fromMilliseconds(50)}), std::runtime_error);
}
