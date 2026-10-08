/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 
 * 
 * This header is intentionally not public because all public functions for
 * firmware update are in the sensor configurator classes.
 */

#pragma once

#include "HttpHelpers.hpp"
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace sick::firmware_update {

using namespace std::chrono_literals;

/**
 * @brief Injection seam for time.
 *
 * The defaults call the real clock and block the calling thread. Tests override @a now and @a wait
 * (and shorten @a pollInterval) to drive the poll loop deterministically and without real waiting.
 */
struct TimeProvider
{
  std::function<Timestamp()> now = []() -> Timestamp {
    return Timestamp::now();
  };
  std::function<void(std::chrono::milliseconds)> wait = [](std::chrono::milliseconds duration) -> void {
    std::this_thread::sleep_for(duration);
  };
  std::chrono::milliseconds pollInterval = 1s;
};

/**
 * @brief Upload and apply a firmware image to the sensor.
 *
 * @param firmwareData Raw bytes of the firmware image, e.g. loaded via @ref sick::loadBinaryFile.
 * @param timeout When set, the call blocks and polls the update status until the update finishes,
 * fails, or the timeout elapses. When left empty (@c std::nullopt) the update is only triggered and
 * the call returns immediately without waiting for completion.
 */
template <class EndpointsT, class UpdateStateRequestT>
void run(
  std::vector<std::uint8_t> const& firmwareData,
  SopasClient const& sopasClient,
  EndpointsT const& endpoints,
  std::optional<Duration> timeout = std::nullopt,
  TimeProvider const& time        = {}
)
{
  if (firmwareData.empty())
  {
    throw std::runtime_error("Firmware image is empty.");
  }

  auto const startTime = time.now();

  // Request 1: upload the firmware to the device.
  // The device will not respond with anything else than 200, even if the firmware image is invalid
  // or not acceptable for the device.
  std::string const firmwareDataString(firmwareData.begin(), firmwareData.end());

  HttpRequest request;
  request.method          = HttpMethod::Put;
  request.path            = "/api/update";
  request.contentType     = "application/octet-stream";
  request.body            = firmwareDataString;
  auto const sessionToken = sopasClient.createSessionToken();
  request.headers         = sessionHeaders(sessionToken);
  auto const response     = sopasClient.httpClient().send(request);
  throwIfNotOk(response, "Upload of firmware");

  // Request 2: trigger the firmware update process on the device.
  endpoints.runFirmwareUpdate();

  if (!timeout.has_value())
  {
    return;
  }

  // Request 3: poll the update status until it is finished or an error occurs, or until the timeout is reached.
  // Here the device will actually report an error if the firmware image is invalid or not acceptable for the device.
  while (true)
  {
    auto const elapsedTime = time.now() - startTime;
    if (elapsedTime > timeout.value())
    {
      throw std::runtime_error("Firmware update timed out after " + std::to_string(elapsedTime.seconds()) + " seconds.");
    }

    auto updateState = UpdateStateRequestT::Get::Response::UpdateState::Initial;
    try
    {
      updateState = endpoints.getUpdateState();
    }
    // Silently ignore any runtime errors during the polling of the update state.
    // They may occur if the device does not respond during the update process.
    catch (std::runtime_error const&)
    {
      continue;
    }

    if (updateState == UpdateStateRequestT::Get::Response::UpdateState::Error)
    {
      throw std::runtime_error("Firmware update failed with error state.");
    }

    if (updateState == UpdateStateRequestT::Get::Response::UpdateState::Finished)
    {
      return;
    }

    time.wait(time.pollInterval);
  }
}

} // namespace sick::firmware_update
