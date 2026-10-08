/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "HttpHelpers.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

namespace {

TEST(HttpHelpersTest, sessionHeaders_returns_single_session_token_header)
{
  auto const headers = sick::sessionHeaders("my-token");

  ASSERT_EQ(headers.size(), 1U);
  EXPECT_EQ(headers[0].first, "X-Session-Token");
  EXPECT_EQ(headers[0].second, "my-token");
}

TEST(HttpHelpersTest, throwIfNotOk_with_status_ok_does_not_throw)
{
  sick::HttpResponse response;
  response.statusCode = 200;

  EXPECT_NO_THROW(sick::throwIfNotOk(response, "context"));
}

TEST(HttpHelpersTest, throwIfNotOk_ok_with_error_status_throws_with_context_and_status)
{
  sick::HttpResponse response;
  response.statusCode = 404;

  try
  {
    sick::throwIfNotOk(response, "Download of parameter backup");
    FAIL() << "expected std::runtime_error";
  }
  catch (std::runtime_error const& error)
  {
    std::string const message = error.what();
    EXPECT_NE(message.find("Download of parameter backup"), std::string::npos);
    EXPECT_NE(message.find("404"), std::string::npos);
  }
}

} // namespace
