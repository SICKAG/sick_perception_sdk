/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>

#include "../FirmwareUpdate.hpp"
#include "../ParameterBackupRestore.hpp"
#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/loadBinaryFile.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Convert.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

namespace sick::multiScan100::v2_4_4 {

Configurator::Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : Endpoints(std::move(httpClient), userLevel, std::move(password))
{ }

void Configurator::enableImuStreamingCompactUdp(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  using Payload = api::rest::ImuDataEthSettings::Post::Request;
  Payload const payload {Payload::Protocol::Udp, destinationAddress.bytesVector(), destinationPort};
  setImuDataEthSettings(payload);
  setImuDataEnable(true);
}

void Configurator::enableScanDataStreamingCompactUdp(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  {
    using Payload = api::rest::ScanDataEthSettings::Post::Request;
    Payload const payload {Payload::Protocol::Udp, destinationAddress.bytesVector(), destinationPort};
    setScanDataEthSettings(payload);
  }

  {
    using Payload = api::rest::ScanDataFormat::Post::Request;
    setScanDataFormat(Payload::ScanDataFormat::Compact);
  }

  setScanDataEnable(true);
}

auto Configurator::getSystemTimeOfSensor() const -> Timestamp
{
  return convert::toTimestamp(getLSPdatetime());
}

auto Configurator::backupParameters(std::string const& passphrase, Duration timeout) const -> std::string
{
  createParameterBackup(passphrase);
  std::this_thread::sleep_for(timeout.toChrono()); // Device does not report the status, so we just wait for the backup creation to finish.
  return parameters::backup::fetchFromSensor(*m_sopasClient);
}

void Configurator::restoreParameters(std::string const& backupContent, std::string const& passphrase, Duration timeout) const
{
  parameters::restore::uploadToSensor(backupContent, *m_sopasClient);

  auto const response = restoreParameterBackup(passphrase);
  if (response._RestoreResult != api::rest::RestoreParameterBackup::Post::Response::RestoreResult::Ok)
  {
    throw std::runtime_error("RestoreParameterBackup failed with result: " + std::to_string(static_cast<int>(response._RestoreResult)));
  }

  std::this_thread::sleep_for(timeout.toChrono()); // Device does not report the status, so we just wait for the backup creation to finish.
}

void Configurator::updateFirmware(std::string const& firmwareFilePath, std::optional<Duration> timeout) const
{
  firmware_update::run<Endpoints, api::rest::UpdateState>(loadBinaryFile(firmwareFilePath), *m_sopasClient, *this, timeout);
}

} // namespace sick::multiScan100::v2_4_4
