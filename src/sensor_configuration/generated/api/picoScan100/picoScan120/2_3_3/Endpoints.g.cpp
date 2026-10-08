/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.cpp Generated Endpoints implementation.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3/Endpoints.g.hpp>

#include <sick_perception_sdk/sensor_configuration/SopasClientImpl.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_3_3.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <utility>

namespace sick::picoScan120::v2_3_3 {

Endpoints::Endpoints(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : m_sopasClient(std::make_unique<SopasClient>(httpClient, userLevel, password))
{}

auto Endpoints::changePassword(api::rest::changePassword::Post::Request const& request) const -> decltype(api::rest::changePassword::Post::Response::_result)
{
  return m_sopasClient->invokeMethod<api::rest::changePassword>(request)._result;
}

void Endpoints::checkCredentials() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::checkCredentials>();
}

auto Endpoints::createParameterBackup(decltype(api::rest::CreateParameterBackup::Post::Request::_Passphrase) const& value) const -> decltype(api::rest::CreateParameterBackup::Post::Response::_Result)
{
  return m_sopasClient->invokeMethod<api::rest::CreateParameterBackup>(api::rest::CreateParameterBackup::Post::Request{value})._Result;
}

auto Endpoints::createSessionToken() const -> api::rest::CreateSessionToken::Post::Response
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::CreateSessionToken>();
}

auto Endpoints::doDiagnosisDump(api::rest::DoDiagnosisDump::Post::Request const& request) const -> decltype(api::rest::DoDiagnosisDump::Post::Response::_Successfull)
{
  return m_sopasClient->invokeMethod<api::rest::DoDiagnosisDump>(request)._Successfull;
}

auto Endpoints::enableLegacyUserLevel(api::rest::EnableLegacyUserLevel::Post::Request const& request) const -> decltype(api::rest::EnableLegacyUserLevel::Post::Response::_result)
{
  return m_sopasClient->invokeMethod<api::rest::EnableLegacyUserLevel>(request)._result;
}

auto Endpoints::enableUserLevel(api::rest::EnableUserLevel::Post::Request const& request) const -> decltype(api::rest::EnableUserLevel::Post::Response::_result)
{
  return m_sopasClient->invokeMethod<api::rest::EnableUserLevel>(request)._result;
}

void Endpoints::ethernetUpdate() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::EthernetUpdate>();
}

void Endpoints::findMe(decltype(api::rest::FindMe::Post::Request::_uiDuration) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::FindMe>(api::rest::FindMe::Post::Request{value});
}

auto Endpoints::getAutoStartMeasure() const -> decltype(api::rest::AutoStartMeasure::Get::Response::_AutoStartMeasure)
{
  return m_sopasClient->readVariable<api::rest::AutoStartMeasure>()._AutoStartMeasure;
}

auto Endpoints::getCertificateBundleInfo() const -> api::rest::certificateBundleInfo::Get::Response
{
  return m_sopasClient->readVariable<api::rest::certificateBundleInfo>();
}

void Endpoints::getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::getChallenge>(api::rest::getChallenge::Post::Request{value});
}

auto Endpoints::getCompactTelegramType1Content() const -> api::rest::compactTelegramType1Content::Get::Response
{
  return m_sopasClient->readVariable<api::rest::compactTelegramType1Content>();
}

auto Endpoints::getCreateParameterBackupResult() const -> api::rest::CreateParameterBackupResult::Get::Response
{
  return m_sopasClient->readVariable<api::rest::CreateParameterBackupResult>();
}

auto Endpoints::getCurrentTempDev() const -> decltype(api::rest::CurrentTempDev::Get::Response::_CurrentTempDev)
{
  return m_sopasClient->readVariable<api::rest::CurrentTempDev>()._CurrentTempDev;
}

auto Endpoints::getDailyOpHours() const -> decltype(api::rest::DailyOpHours::Get::Response::_DailyOpHours)
{
  return m_sopasClient->readVariable<api::rest::DailyOpHours>()._DailyOpHours;
}

auto Endpoints::getDeviceIdent() const -> api::rest::DeviceIdent::Get::Response
{
  return m_sopasClient->readVariable<api::rest::DeviceIdent>();
}

auto Endpoints::getDeviceStatus() const -> decltype(api::rest::DeviceStatus::Get::Response::_DeviceStatus)
{
  return m_sopasClient->readVariable<api::rest::DeviceStatus>()._DeviceStatus;
}

auto Endpoints::getDeviceType() const -> decltype(api::rest::DeviceType::Get::Response::_DeviceType)
{
  return m_sopasClient->readVariable<api::rest::DeviceType>()._DeviceType;
}

auto Endpoints::getDiagnosisDumpInfo() const -> api::rest::GetDiagnosisDumpInfo::Post::Response
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::GetDiagnosisDumpInfo>();
}

auto Endpoints::getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode)
{
  return m_sopasClient->readVariable<api::rest::EtherAddressingMode>()._EtherAddressingMode;
}

auto Endpoints::getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled)
{
  return m_sopasClient->readVariable<api::rest::EtherAuxEnabled>()._EtherAuxEnabled;
}

auto Endpoints::getEtherAuxIPPort() const -> decltype(api::rest::EtherAuxIPPort::Get::Response::_EtherAuxIPPort)
{
  return m_sopasClient->readVariable<api::rest::EtherAuxIPPort>()._EtherAuxIPPort;
}

auto Endpoints::getEtherCoLaScanMode() const -> decltype(api::rest::EtherCoLaScanMode::Get::Response::_EtherCoLaScanMode)
{
  return m_sopasClient->readVariable<api::rest::EtherCoLaScanMode>()._EtherCoLaScanMode;
}

auto Endpoints::getEtherDHCPFallback() const -> decltype(api::rest::EtherDHCPFallback::Get::Response::_EtherDHCPFallback)
{
  return m_sopasClient->readVariable<api::rest::EtherDHCPFallback>()._EtherDHCPFallback;
}

auto Endpoints::getEtherHostIPPort() const -> decltype(api::rest::EtherHostIPPort::Get::Response::_EtherHostIPPort)
{
  return m_sopasClient->readVariable<api::rest::EtherHostIPPort>()._EtherHostIPPort;
}

auto Endpoints::getEtherIPAddress() const -> decltype(api::rest::EtherIPAddress::Get::Response::_EtherIPAddress)
{
  return m_sopasClient->readVariable<api::rest::EtherIPAddress>()._EtherIPAddress;
}

auto Endpoints::getEtherIPAddressDHCP() const -> decltype(api::rest::EtherIPAddressDHCP::Get::Response::_EtherIPAddressDHCP)
{
  return m_sopasClient->readVariable<api::rest::EtherIPAddressDHCP>()._EtherIPAddressDHCP;
}

auto Endpoints::getEtherIPGateAddress() const -> decltype(api::rest::EtherIPGateAddress::Get::Response::_EtherIPGateAddress)
{
  return m_sopasClient->readVariable<api::rest::EtherIPGateAddress>()._EtherIPGateAddress;
}

auto Endpoints::getEtherIPGateAddressDHCP() const -> decltype(api::rest::EtherIPGateAddressDHCP::Get::Response::_EtherIPGateAddressDHCP)
{
  return m_sopasClient->readVariable<api::rest::EtherIPGateAddressDHCP>()._EtherIPGateAddressDHCP;
}

auto Endpoints::getEtherIPMask() const -> decltype(api::rest::EtherIPMask::Get::Response::_EtherIPMask)
{
  return m_sopasClient->readVariable<api::rest::EtherIPMask>()._EtherIPMask;
}

auto Endpoints::getEtherIPMaskDHCP() const -> decltype(api::rest::EtherIPMaskDHCP::Get::Response::_EtherIPMaskDHCP)
{
  return m_sopasClient->readVariable<api::rest::EtherIPMaskDHCP>()._EtherIPMaskDHCP;
}

auto Endpoints::getEtherMACAddress() const -> decltype(api::rest::EtherMACAddress::Get::Response::_EtherMACAddress)
{
  return m_sopasClient->readVariable<api::rest::EtherMACAddress>()._EtherMACAddress;
}

auto Endpoints::getEtherSessionTimeout() const -> decltype(api::rest::EtherSessionTimeout::Get::Response::_EtherSessionTimeout)
{
  return m_sopasClient->readVariable<api::rest::EtherSessionTimeout>()._EtherSessionTimeout;
}

auto Endpoints::getFirmwareVersion() const -> decltype(api::rest::FirmwareVersion::Get::Response::_FirmwareVersion)
{
  return m_sopasClient->readVariable<api::rest::FirmwareVersion>()._FirmwareVersion;
}

auto Endpoints::getHttpsStatus() const -> api::rest::httpsStatus::Get::Response
{
  return m_sopasClient->readVariable<api::rest::httpsStatus>();
}

auto Endpoints::getLEDEnable() const -> decltype(api::rest::LEDEnable::Get::Response::_LEDEnable)
{
  return m_sopasClient->readVariable<api::rest::LEDEnable>()._LEDEnable;
}

auto Endpoints::getLEDState() const -> decltype(api::rest::LEDState::Get::Response::_LEDState)
{
  return m_sopasClient->readVariable<api::rest::LEDState>()._LEDState;
}

auto Endpoints::getLFPparticle() const -> api::rest::LFPparticle::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFPparticle>();
}

auto Endpoints::getLFTchecksum() const -> api::rest::LFTchecksum::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFTchecksum>();
}

auto Endpoints::getLSPdatetime() const -> decltype(api::rest::LSPdatetime::Get::Response::_LSPdatetime)
{
  return m_sopasClient->readVariable<api::rest::LSPdatetime>()._LSPdatetime;
}

auto Endpoints::getLaserType() const -> decltype(api::rest::laserType::Get::Response::_laserType)
{
  return m_sopasClient->readVariable<api::rest::laserType>()._laserType;
}

auto Endpoints::getLastParaDate() const -> decltype(api::rest::LastParaDate::Get::Response::_LastParaDate)
{
  return m_sopasClient->readVariable<api::rest::LastParaDate>()._LastParaDate;
}

auto Endpoints::getLastParaTime() const -> decltype(api::rest::LastParaTime::Get::Response::_LastParaTime)
{
  return m_sopasClient->readVariable<api::rest::LastParaTime>()._LastParaTime;
}

auto Endpoints::getLocationName() const -> decltype(api::rest::LocationName::Get::Response::_LocationName)
{
  return m_sopasClient->readVariable<api::rest::LocationName>()._LocationName;
}

auto Endpoints::getOpHours() const -> decltype(api::rest::OpHours::Get::Response::_OpHours)
{
  return m_sopasClient->readVariable<api::rest::OpHours>()._OpHours;
}

auto Endpoints::getOperatingMode() const -> decltype(api::rest::operatingMode::Get::Response::_operatingMode)
{
  return m_sopasClient->readVariable<api::rest::operatingMode>()._operatingMode;
}

auto Endpoints::getOrderNumber() const -> decltype(api::rest::OrderNumber::Get::Response::_OrderNumber)
{
  return m_sopasClient->readVariable<api::rest::OrderNumber>()._OrderNumber;
}

auto Endpoints::getOutputState() const -> api::rest::OutputState::Get::Response
{
  return m_sopasClient->readVariable<api::rest::OutputState>();
}

auto Endpoints::getPortConfiguration() const -> decltype(api::rest::PortConfiguration::Get::Response::_PortConfiguration)
{
  return m_sopasClient->readVariable<api::rest::PortConfiguration>()._PortConfiguration;
}

auto Endpoints::getPortState() const -> api::rest::PortState::Get::Response
{
  return m_sopasClient->readVariable<api::rest::PortState>();
}

auto Endpoints::getPowerOnCnt() const -> decltype(api::rest::PowerOnCnt::Get::Response::_PowerOnCnt)
{
  return m_sopasClient->readVariable<api::rest::PowerOnCnt>()._PowerOnCnt;
}

auto Endpoints::getRestoreParameterBackupResult() const -> api::rest::RestoreParameterBackupResult::Get::Response
{
  return m_sopasClient->readVariable<api::rest::RestoreParameterBackupResult>();
}

auto Endpoints::getRosDomainId() const -> decltype(api::rest::rosDomainId::Get::Response::_rosDomainId)
{
  return m_sopasClient->readVariable<api::rest::rosDomainId>()._rosDomainId;
}

auto Endpoints::getRosFrameId() const -> decltype(api::rest::rosFrameId::Get::Response::_rosFrameId)
{
  return m_sopasClient->readVariable<api::rest::rosFrameId>()._rosFrameId;
}

auto Endpoints::getRosNamespace() const -> decltype(api::rest::rosNamespace::Get::Response::_rosNamespace)
{
  return m_sopasClient->readVariable<api::rest::rosNamespace>()._rosNamespace;
}

auto Endpoints::getRosParentFrameId() const -> decltype(api::rest::rosParentFrameId::Get::Response::_rosParentFrameId)
{
  return m_sopasClient->readVariable<api::rest::rosParentFrameId>()._rosParentFrameId;
}

auto Endpoints::getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate)
{
  return m_sopasClient->readVariable<api::rest::SCdevicestate>()._SCdevicestate;
}

auto Endpoints::getScanConfig() const -> api::rest::ScanConfig::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ScanConfig>();
}

auto Endpoints::getScanDataConfig() const -> api::rest::ScanDataConfig::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ScanDataConfig>();
}

auto Endpoints::getScanDataEnable() const -> decltype(api::rest::ScanDataEnable::Get::Response::_ScanDataEnable)
{
  return m_sopasClient->readVariable<api::rest::ScanDataEnable>()._ScanDataEnable;
}

auto Endpoints::getScanDataEthSettings() const -> api::rest::ScanDataEthSettings::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ScanDataEthSettings>();
}

auto Endpoints::getScanDataFormat() const -> decltype(api::rest::ScanDataFormat::Get::Response::_ScanDataFormat)
{
  return m_sopasClient->readVariable<api::rest::ScanDataFormat>()._ScanDataFormat;
}

auto Endpoints::getSensorPosition() const -> api::rest::SensorPosition::Get::Response
{
  return m_sopasClient->readVariable<api::rest::SensorPosition>();
}

auto Endpoints::getSerialNumber() const -> decltype(api::rest::SerialNumber::Get::Response::_SerialNumber)
{
  return m_sopasClient->readVariable<api::rest::SerialNumber>()._SerialNumber;
}

auto Endpoints::getSipmType() const -> decltype(api::rest::sipmType::Get::Response::_sipmType)
{
  return m_sopasClient->readVariable<api::rest::sipmType>()._sipmType;
}

auto Endpoints::getTSCRole() const -> decltype(api::rest::TSCRole::Get::Response::_TSCRole)
{
  return m_sopasClient->readVariable<api::rest::TSCRole>()._TSCRole;
}

auto Endpoints::getTSCTCSrvAddr() const -> decltype(api::rest::TSCTCSrvAddr::Get::Response::_TSCTCSrvAddr)
{
  return m_sopasClient->readVariable<api::rest::TSCTCSrvAddr>()._TSCTCSrvAddr;
}

auto Endpoints::getTSCTCtimezone() const -> decltype(api::rest::TSCTCtimezone::Get::Response::_TSCTCtimezone)
{
  return m_sopasClient->readVariable<api::rest::TSCTCtimezone>()._TSCTCtimezone;
}

auto Endpoints::getTSCTCupdatetime() const -> decltype(api::rest::TSCTCupdatetime::Get::Response::_TSCTCupdatetime)
{
  return m_sopasClient->readVariable<api::rest::TSCTCupdatetime>()._TSCTCupdatetime;
}

auto Endpoints::getTemperatureAlarmConfiguration() const -> api::rest::temperatureAlarmConfiguration::Get::Response
{
  return m_sopasClient->readVariable<api::rest::temperatureAlarmConfiguration>();
}

auto Endpoints::getTemperatureAlarmStatus() const -> decltype(api::rest::temperatureAlarmStatus::Get::Response::_temperatureAlarmStatus)
{
  return m_sopasClient->readVariable<api::rest::temperatureAlarmStatus>()._temperatureAlarmStatus;
}

auto Endpoints::getUpdateState() const -> decltype(api::rest::UpdateState::Get::Response::_UpdateState)
{
  return m_sopasClient->readVariable<api::rest::UpdateState>()._UpdateState;
}

auto Endpoints::getWebserverEnabled() const -> decltype(api::rest::GetWebserverEnabled::Post::Response::_IsEnabled)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::GetWebserverEnabled>()._IsEnabled;
}

auto Endpoints::lSPsetdatetime(decltype(api::rest::LSPsetdatetime::Post::Request::_DateTime) const& value) const -> decltype(api::rest::LSPsetdatetime::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::LSPsetdatetime>(api::rest::LSPsetdatetime::Post::Request{value})._ErrorCode;
}

void Endpoints::loadApplicationDefaults() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::LoadApplicationDefaults>();
}

void Endpoints::loadFactoryDefaults() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::LoadFactoryDefaults>();
}

auto Endpoints::mResetOutputCounter() const -> decltype(api::rest::mResetOutputCounter::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mResetOutputCounter>()._ErrorCode;
}

auto Endpoints::mStandby() const -> decltype(api::rest::mStandby::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mStandby>()._ErrorCode;
}

auto Endpoints::mStartMeasure() const -> decltype(api::rest::mStartMeasure::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mStartMeasure>()._ErrorCode;
}

auto Endpoints::mStopMeasure() const -> decltype(api::rest::mStopMeasure::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mStopMeasure>()._ErrorCode;
}

void Endpoints::rebootDevice() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::RebootDevice>();
}

auto Endpoints::removeCertificateBundle() const -> api::rest::removeCertificateBundle::Post::Response
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::removeCertificateBundle>();
}

auto Endpoints::restoreParameterBackup(api::rest::RestoreParameterBackup::Post::Request const& request) const -> decltype(api::rest::RestoreParameterBackup::Post::Response::_Result)
{
  return m_sopasClient->invokeMethod<api::rest::RestoreParameterBackup>(request)._Result;
}

void Endpoints::runFirmwareUpdate() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::RunFirmwareUpdate>();
}

void Endpoints::setAutoStartMeasure(decltype(api::rest::AutoStartMeasure::Post::Request::_AutoStartMeasure) const& value) const
{
  m_sopasClient->writeVariable<api::rest::AutoStartMeasure>(api::rest::AutoStartMeasure::Post::Request{value});
}

auto Endpoints::setCertificateBundle(api::rest::setCertificateBundle::Post::Request const& request) const -> api::rest::setCertificateBundle::Post::Response
{
  return m_sopasClient->invokeMethod<api::rest::setCertificateBundle>(request);
}

void Endpoints::setCompactTelegramType1Content(api::rest::compactTelegramType1Content::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::compactTelegramType1Content>(request);
}

void Endpoints::setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAddressingMode>(api::rest::EtherAddressingMode::Post::Request{value});
}

void Endpoints::setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAuxEnabled>(api::rest::EtherAuxEnabled::Post::Request{value});
}

void Endpoints::setEtherAuxIPPort(decltype(api::rest::EtherAuxIPPort::Post::Request::_EtherAuxIPPort) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAuxIPPort>(api::rest::EtherAuxIPPort::Post::Request{value});
}

void Endpoints::setEtherCoLaScanMode(decltype(api::rest::EtherCoLaScanMode::Post::Request::_EtherCoLaScanMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherCoLaScanMode>(api::rest::EtherCoLaScanMode::Post::Request{value});
}

void Endpoints::setEtherDHCPFallback(decltype(api::rest::EtherDHCPFallback::Post::Request::_EtherDHCPFallback) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherDHCPFallback>(api::rest::EtherDHCPFallback::Post::Request{value});
}

void Endpoints::setEtherHostIPPort(decltype(api::rest::EtherHostIPPort::Post::Request::_EtherHostIPPort) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherHostIPPort>(api::rest::EtherHostIPPort::Post::Request{value});
}

void Endpoints::setEtherIPAddress(decltype(api::rest::EtherIPAddress::Post::Request::_EtherIPAddress) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherIPAddress>(api::rest::EtherIPAddress::Post::Request{value});
}

void Endpoints::setEtherIPGateAddress(decltype(api::rest::EtherIPGateAddress::Post::Request::_EtherIPGateAddress) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherIPGateAddress>(api::rest::EtherIPGateAddress::Post::Request{value});
}

void Endpoints::setEtherIPMask(decltype(api::rest::EtherIPMask::Post::Request::_EtherIPMask) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherIPMask>(api::rest::EtherIPMask::Post::Request{value});
}

void Endpoints::setEtherSessionTimeout(decltype(api::rest::EtherSessionTimeout::Post::Request::_EtherSessionTimeout) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherSessionTimeout>(api::rest::EtherSessionTimeout::Post::Request{value});
}

void Endpoints::setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LEDEnable>(api::rest::LEDEnable::Post::Request{value});
}

void Endpoints::setLFPparticle(api::rest::LFPparticle::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::LFPparticle>(request);
}

void Endpoints::setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LocationName>(api::rest::LocationName::Post::Request{value});
}

void Endpoints::setOperatingMode(decltype(api::rest::operatingMode::Post::Request::_operatingMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::operatingMode>(api::rest::operatingMode::Post::Request{value});
}

auto Endpoints::setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success)
{
  return m_sopasClient->invokeMethod<api::rest::SetOutput>(request)._Success;
}

auto Endpoints::setPassword(api::rest::SetPassword::Post::Request const& request) const -> decltype(api::rest::SetPassword::Post::Response::_bSuccess)
{
  return m_sopasClient->invokeMethod<api::rest::SetPassword>(request)._bSuccess;
}

void Endpoints::setPortConfiguration(decltype(api::rest::PortConfiguration::Post::Request::_PortConfiguration) const& value) const
{
  m_sopasClient->writeVariable<api::rest::PortConfiguration>(api::rest::PortConfiguration::Post::Request{value});
}

void Endpoints::setRosDomainId(decltype(api::rest::rosDomainId::Post::Request::_rosDomainId) const& value) const
{
  m_sopasClient->writeVariable<api::rest::rosDomainId>(api::rest::rosDomainId::Post::Request{value});
}

void Endpoints::setRosFrameId(decltype(api::rest::rosFrameId::Post::Request::_rosFrameId) const& value) const
{
  m_sopasClient->writeVariable<api::rest::rosFrameId>(api::rest::rosFrameId::Post::Request{value});
}

void Endpoints::setRosNamespace(decltype(api::rest::rosNamespace::Post::Request::_rosNamespace) const& value) const
{
  m_sopasClient->writeVariable<api::rest::rosNamespace>(api::rest::rosNamespace::Post::Request{value});
}

void Endpoints::setRosParentFrameId(decltype(api::rest::rosParentFrameId::Post::Request::_rosParentFrameId) const& value) const
{
  m_sopasClient->writeVariable<api::rest::rosParentFrameId>(api::rest::rosParentFrameId::Post::Request{value});
}

void Endpoints::setScanDataConfig(api::rest::ScanDataConfig::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataConfig>(request);
}

void Endpoints::setScanDataEnable(decltype(api::rest::ScanDataEnable::Post::Request::_ScanDataEnable) const& value) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataEnable>(api::rest::ScanDataEnable::Post::Request{value});
}

void Endpoints::setScanDataEthSettings(api::rest::ScanDataEthSettings::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataEthSettings>(request);
}

void Endpoints::setScanDataFormat(decltype(api::rest::ScanDataFormat::Post::Request::_ScanDataFormat) const& value) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataFormat>(api::rest::ScanDataFormat::Post::Request{value});
}

void Endpoints::setSensorPosition(api::rest::SensorPosition::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::SensorPosition>(request);
}

void Endpoints::setTSCRole(decltype(api::rest::TSCRole::Post::Request::_TSCRole) const& value) const
{
  m_sopasClient->writeVariable<api::rest::TSCRole>(api::rest::TSCRole::Post::Request{value});
}

void Endpoints::setTSCTCSrvAddr(decltype(api::rest::TSCTCSrvAddr::Post::Request::_TSCTCSrvAddr) const& value) const
{
  m_sopasClient->writeVariable<api::rest::TSCTCSrvAddr>(api::rest::TSCTCSrvAddr::Post::Request{value});
}

void Endpoints::setTSCTCtimezone(decltype(api::rest::TSCTCtimezone::Post::Request::_TSCTCtimezone) const& value) const
{
  m_sopasClient->writeVariable<api::rest::TSCTCtimezone>(api::rest::TSCTCtimezone::Post::Request{value});
}

void Endpoints::setTSCTCupdatetime(decltype(api::rest::TSCTCupdatetime::Post::Request::_TSCTCupdatetime) const& value) const
{
  m_sopasClient->writeVariable<api::rest::TSCTCupdatetime>(api::rest::TSCTCupdatetime::Post::Request{value});
}

void Endpoints::setTemperatureAlarmConfiguration(api::rest::temperatureAlarmConfiguration::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::temperatureAlarmConfiguration>(request);
}

void Endpoints::setWebserverEnabled(decltype(api::rest::SetWebserverEnabled::Post::Request::_Enable) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SetWebserverEnabled>(api::rest::SetWebserverEnabled::Post::Request{value});
}

void Endpoints::softReset(decltype(api::rest::SoftReset::Post::Request::_ProcessorNbr) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SoftReset>(api::rest::SoftReset::Post::Request{value});
}

auto Endpoints::writeEeprom() const -> decltype(api::rest::WriteEeprom::Post::Response::_Success)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::WriteEeprom>()._Success;
}

} // namespace sick::picoScan120::v2_3_3
