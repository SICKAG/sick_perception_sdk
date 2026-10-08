/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 
 * 
 * This header is intentionally not public because all public functions for
 * parameter backup and restore are in the sensor configurator classes.
 */

#pragma once

#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>

#include <chrono>
#include <exception>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace sick::parameters {

constexpr auto pollInterval          = std::chrono::milliseconds(100);
constexpr auto defaultBackupTimeout  = Duration::fromSeconds(30);
constexpr auto defaultRestoreTimeout = Duration::fromSeconds(30);

/**
 * @brief Internal helpers to fetch a parameter backup via REST.
 * 
 * The typical backup sequence is:
 * 1. Create the backup on the sensor (POST `/api/CreateParameterBackup`).
 * 2. Wait for the backup to be ready (pollState() or wait for an appropriate amount of time).
 * 3. Fetch the backup (GET `/api/parameterbackup`).
 */
namespace backup {

/**
 * @brief Fetch a parameter backup via REST.
 * 
 * Make sure to follow the typical @ref sick::parameters::backup sequence before calling this function.
 * 
 * @returns The binary response from a sensor backup encoded as string.
 * @throws std::runtime_error if the fetch request fails.
 */
auto fetchFromSensor(SopasClient const& sopasClient) -> std::string;

/**
 * @brief Poll the state of a parameter backup creation until it is finished or a timeout occurs.
 * 
 * @warning Not all sensors support this. If the sensor does not support it, the caller must wait for an appropriate amount of time before calling fetchFromSensor().
 */
template <class EndpointsT, class CreateParameterBackupResultT>
void pollState(EndpointsT const& endpoints, Duration timeout = defaultBackupTimeout)
{
  auto const startTime = Timestamp::now();
  while (true)
  {
    auto const elapsedTime = Timestamp::now() - startTime;
    if (elapsedTime > timeout)
    {
      throw std::runtime_error("Parameter backup creation timed out after " + std::to_string(elapsedTime.seconds()) + " seconds.");
    }

    auto const result = endpoints.getCreateParameterBackupResult();
    if (result._Status == CreateParameterBackupResultT::Get::Response::Status::Finished)
    {
      if (!result._Result)
      {
        throw std::runtime_error("Parameter backup creation failed.");
      }
      return;
    }

    std::this_thread::sleep_for(pollInterval);
  }
}

} // namespace backup

/**
 * @brief Internal helpers to restore a parameter backup via REST.
 * 
 * The typical restore sequence is:
 * 1. Upload the backup to the sensor (PUT `/api/parameterbackup`).
 * 2. Trigger the restore on the sensor (POST `/api/RestoreParameterBackup`).
 * 3. Wait for the restore to be finished (pollState() or wait for an appropriate amount of time).
 */
namespace restore {

struct ParameterRestoreException : public std::runtime_error
{
  ParameterRestoreException(int resultCode, std::vector<std::string> failedParameterIds)
    : std::runtime_error("Parameter restore failed with result code " + std::to_string(resultCode))
    , m_resultCode(resultCode)
    , m_failedParameterIds(std::move(failedParameterIds))
  { }

  auto resultCode() const -> int
  {
    return m_resultCode;
  }

  auto failedParameterIds() const -> std::vector<std::string> const&
  {
    return m_failedParameterIds;
  }

private:
  int m_resultCode;
  std::vector<std::string> m_failedParameterIds;
};

/**
 * @brief Upload a parameter backup to the sensor via REST.
 * 
 * @param backupContent The binary response from a previous parameter backup encoded as string.
 * 
 * @throws std::runtime_error if the upload request fails.
 */
void uploadToSensor(std::string const& backupContent, SopasClient const& sopasClient);

/**
 * @brief Poll the state of a parameter restore until it is finished or a timeout occurs.
 * 
 * @warning Not all sensors support this. If the sensor does not support it, the caller must wait for an appropriate amount of time after calling uploadToSensor() or just assume the restore is finished.
 */
template <class EndpointsT, class RestoreParameterBackupResultT>
void pollState(EndpointsT const& endpoints, Duration timeout = defaultRestoreTimeout)
{
  auto const startTime = Timestamp::now();
  while (true)
  {
    auto const elapsedTime = Timestamp::now() - startTime;
    if (elapsedTime > timeout)
    {
      throw std::runtime_error("Parameter restore timed out after " + std::to_string(elapsedTime.seconds()) + " seconds.");
    }

    auto const result = endpoints.getRestoreParameterBackupResult();
    if (result._Status == RestoreParameterBackupResultT::Get::Response::Status::Finished)
    {
      if (result._RestoreResult != RestoreParameterBackupResultT::Get::Response::RestoreResult::Ok)
      {
        throw ParameterRestoreException(static_cast<int>(result._RestoreResult), result._ParametersFailedToRestore);
      }
      return;
    }

    std::this_thread::sleep_for(pollInterval);
  }
}

} // namespace restore

} // namespace sick::parameters
