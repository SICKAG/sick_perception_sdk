/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>

#include "../FirmwareUpdate.hpp"
#include "../ParameterBackupRestore.hpp"
#include <sick_perception_sdk/common/loadBinaryFile.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Convert.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace sick::multiScan200::v1_1_0 {

Configurator::Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : Endpoints(std::move(httpClient), userLevel, std::move(password))
{ }

void Configurator::enableScanDataStreamingCompactTcp() const
{
  setDataOutputMode(api::rest::dataOutputMode::Post::Request::dataOutputMode::TcpCompact);
}

auto Configurator::getSystemTimeOfSensor() const -> Timestamp
{
  return convert::toTimestamp(getLSPdatetime());
}

auto Configurator::backupParameters(std::string const& passphrase, Duration timeout) const -> std::string
{
  createParameterBackup(passphrase);
  parameters::backup::pollState<Endpoints, api::rest::CreateParameterBackupResult>(*this, timeout);
  return parameters::backup::fetchFromSensor(*m_sopasClient);
}

void Configurator::restoreParameters(std::string const& backupContent, std::string const& passphrase, Duration timeout) const
{
  parameters::restore::uploadToSensor(backupContent, *m_sopasClient);

  // Filter 0 restores all parameters.
  auto const response = restoreParameterBackup(api::rest::RestoreParameterBackup::Post::Request {passphrase, 0});
  if (!response)
  {
    throw std::runtime_error("RestoreParameterBackup failed");
  }

  parameters::restore::pollState<Endpoints, api::rest::RestoreParameterBackupResult>(*this, timeout);
}

void Configurator::updateFirmware(std::string const& firmwareFilePath, std::optional<Duration> timeout) const
{
  firmware_update::run<Endpoints, api::rest::UpdateState>(loadBinaryFile(firmwareFilePath), *m_sopasClient, *this, timeout);
}

} // namespace sick::multiScan200::v1_1_0
