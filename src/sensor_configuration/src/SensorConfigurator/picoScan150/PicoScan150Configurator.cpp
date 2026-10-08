/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>

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
#include <utility>

namespace sick::picoScan150::v2_3_3 {

Configurator::Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : Endpoints(std::move(httpClient), userLevel, std::move(password))
{ }

void Configurator::enableEncoderStreamingCompactUdp(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  using Payload = api::rest::EncoderDataEthSettings::Post::Request;
  Payload const payload {Payload::Protocol::Udp, destinationAddress.bytesVector(), destinationPort};
  setEncoderDataEthSettings(payload);
  setEncoderDataEnable(true);
}

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
  parameters::backup::pollState<Endpoints, api::rest::CreateParameterBackupResult>(*this, timeout);
  return parameters::backup::fetchFromSensor(*m_sopasClient);
}

void Configurator::restoreParameters(std::string const& backupContent, std::string const& passphrase, Duration timeout, std::uint32_t filter) const
{
  parameters::restore::uploadToSensor(backupContent, *m_sopasClient);

  api::rest::RestoreParameterBackup::Post::Request const restoreRequest {passphrase, filter};
  auto const wasSuccessful = restoreParameterBackup(restoreRequest);
  if (!wasSuccessful)
  {
    throw std::runtime_error("Parameter restore failed");
  }

  parameters::restore::pollState<Endpoints, api::rest::RestoreParameterBackupResult>(*this, timeout);
}

void Configurator::updateFirmware(std::string const& firmwareFilePath, std::optional<Duration> timeout) const
{
  firmware_update::run<Endpoints, api::rest::UpdateState>(loadBinaryFile(firmwareFilePath), *m_sopasClient, *this, timeout);
}

} // namespace sick::picoScan150::v2_3_3
