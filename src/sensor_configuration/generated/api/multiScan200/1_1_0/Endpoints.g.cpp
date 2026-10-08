/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.cpp Generated Endpoints implementation.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */

#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0/Endpoints.g.hpp>

#include <sick_perception_sdk/sensor_configuration/SopasClientImpl.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <utility>

namespace sick::multiScan200::v1_1_0 {

Endpoints::Endpoints(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : m_sopasClient(std::make_unique<SopasClient>(httpClient, userLevel, password))
{}

auto Endpoints::activateEvaluationGroup(decltype(api::rest::ActivateEvaluationGroup::Post::Request::_List) const& value) const -> decltype(api::rest::ActivateEvaluationGroup::Post::Response::_Success)
{
  return m_sopasClient->invokeMethod<api::rest::ActivateEvaluationGroup>(api::rest::ActivateEvaluationGroup::Post::Request{value})._Success;
}

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

auto Endpoints::getAmbientPixelCountVertical() const -> decltype(api::rest::ambientPixelCountVertical::Get::Response::_ambientPixelCountVertical)
{
  return m_sopasClient->readVariable<api::rest::ambientPixelCountVertical>()._ambientPixelCountVertical;
}

auto Endpoints::getAngleRangeFocusFilter() const -> api::rest::angleRangeFocusFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::angleRangeFocusFilter>();
}

auto Endpoints::getAutoStartMeasure() const -> decltype(api::rest::AutoStartMeasure::Get::Response::_AutoStartMeasure)
{
  return m_sopasClient->readVariable<api::rest::AutoStartMeasure>()._AutoStartMeasure;
}

auto Endpoints::getBloomingFilter() const -> api::rest::bloomingFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::bloomingFilter>();
}

auto Endpoints::getCertificateBundleInfo() const -> api::rest::certificateBundleInfo::Get::Response
{
  return m_sopasClient->readVariable<api::rest::certificateBundleInfo>();
}

void Endpoints::getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::getChallenge>(api::rest::getChallenge::Post::Request{value});
}

auto Endpoints::getCompactTelegramType6Content() const -> api::rest::compactTelegramType6Content::Get::Response
{
  return m_sopasClient->readVariable<api::rest::compactTelegramType6Content>();
}

auto Endpoints::getContaminationActiveSectors() const -> decltype(api::rest::ContaminationActiveSectors::Get::Response::_ContaminationActiveSectors)
{
  return m_sopasClient->readVariable<api::rest::ContaminationActiveSectors>()._ContaminationActiveSectors;
}

auto Endpoints::getContaminationConfig() const -> api::rest::ContaminationConfig::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ContaminationConfig>();
}

auto Endpoints::getContaminationData() const -> decltype(api::rest::ContaminationData::Get::Response::_ContaminationData)
{
  return m_sopasClient->readVariable<api::rest::ContaminationData>()._ContaminationData;
}

auto Endpoints::getContaminationResult() const -> api::rest::ContaminationResult::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ContaminationResult>();
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

auto Endpoints::getDataOutputMode() const -> decltype(api::rest::dataOutputMode::Get::Response::_dataOutputMode)
{
  return m_sopasClient->readVariable<api::rest::dataOutputMode>()._dataOutputMode;
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

auto Endpoints::getEnableHighPrecisionMode() const -> decltype(api::rest::enableHighPrecisionMode::Get::Response::_enableHighPrecisionMode)
{
  return m_sopasClient->readVariable<api::rest::enableHighPrecisionMode>()._enableHighPrecisionMode;
}

auto Endpoints::getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode)
{
  return m_sopasClient->readVariable<api::rest::EtherAddressingMode>()._EtherAddressingMode;
}

auto Endpoints::getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled)
{
  return m_sopasClient->readVariable<api::rest::EtherAuxEnabled>()._EtherAuxEnabled;
}

auto Endpoints::getEtherCoLaScanMode() const -> decltype(api::rest::EtherCoLaScanMode::Get::Response::_EtherCoLaScanMode)
{
  return m_sopasClient->readVariable<api::rest::EtherCoLaScanMode>()._EtherCoLaScanMode;
}

auto Endpoints::getEtherDHCPFallback() const -> decltype(api::rest::EtherDHCPFallback::Get::Response::_EtherDHCPFallback)
{
  return m_sopasClient->readVariable<api::rest::EtherDHCPFallback>()._EtherDHCPFallback;
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

auto Endpoints::getEvaluationConfigState() const -> api::rest::EvaluationConfigState::Get::Response
{
  return m_sopasClient->readVariable<api::rest::EvaluationConfigState>();
}

auto Endpoints::getFREchoFilter() const -> decltype(api::rest::FREchoFilter::Get::Response::_FREchoFilter)
{
  return m_sopasClient->readVariable<api::rest::FREchoFilter>()._FREchoFilter;
}

auto Endpoints::getFieldEvaluationApplicationState() const -> decltype(api::rest::FieldEvaluationApplicationState::Get::Response::_FieldEvaluationApplicationState)
{
  return m_sopasClient->readVariable<api::rest::FieldEvaluationApplicationState>()._FieldEvaluationApplicationState;
}

auto Endpoints::getFieldEvaluationConfiguration(decltype(api::rest::GetFieldEvaluationConfiguration::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationConfiguration::Post::Response::_Configuration)
{
  return m_sopasClient->invokeMethod<api::rest::GetFieldEvaluationConfiguration>(api::rest::GetFieldEvaluationConfiguration::Post::Request{value})._Configuration;
}

auto Endpoints::getFieldEvaluationContour(decltype(api::rest::GetFieldEvaluationContour::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationContour::Post::Response::_Contour)
{
  return m_sopasClient->invokeMethod<api::rest::GetFieldEvaluationContour>(api::rest::GetFieldEvaluationContour::Post::Request{value})._Contour;
}

auto Endpoints::getFieldEvaluationGroupState() const -> decltype(api::rest::FieldEvaluationGroupState::Get::Response::_FieldEvaluationGroupState)
{
  return m_sopasClient->readVariable<api::rest::FieldEvaluationGroupState>()._FieldEvaluationGroupState;
}

auto Endpoints::getFieldEvaluationResult() const -> decltype(api::rest::FieldEvaluationResult::Get::Response::_FieldEvaluationResult)
{
  return m_sopasClient->readVariable<api::rest::FieldEvaluationResult>()._FieldEvaluationResult;
}

auto Endpoints::getFirmwareVersion() const -> decltype(api::rest::FirmwareVersion::Get::Response::_FirmwareVersion)
{
  return m_sopasClient->readVariable<api::rest::FirmwareVersion>()._FirmwareVersion;
}

auto Endpoints::getHorizontalFieldOfViewCenterAngle() const -> decltype(api::rest::horizontalFieldOfViewCenterAngle::Get::Response::_horizontalFieldOfViewCenterAngle)
{
  return m_sopasClient->readVariable<api::rest::horizontalFieldOfViewCenterAngle>()._horizontalFieldOfViewCenterAngle;
}

auto Endpoints::getHttpsStatus() const -> api::rest::httpsStatus::Get::Response
{
  return m_sopasClient->readVariable<api::rest::httpsStatus>();
}

auto Endpoints::getInertialMeasurementUnit() const -> api::rest::InertialMeasurementUnit::Get::Response
{
  return m_sopasClient->readVariable<api::rest::InertialMeasurementUnit>();
}

auto Endpoints::getInputState() const -> api::rest::InputState::Get::Response
{
  return m_sopasClient->readVariable<api::rest::InputState>();
}

auto Endpoints::getLEDEnable() const -> decltype(api::rest::LEDEnable::Get::Response::_LEDEnable)
{
  return m_sopasClient->readVariable<api::rest::LEDEnable>()._LEDEnable;
}

auto Endpoints::getLEDState() const -> decltype(api::rest::LEDState::Get::Response::_LEDState)
{
  return m_sopasClient->readVariable<api::rest::LEDState>()._LEDState;
}

auto Endpoints::getLFPintervalFilter() const -> api::rest::LFPintervalFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFPintervalFilter>();
}

auto Endpoints::getLFTchecksum() const -> api::rest::LFTchecksum::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFTchecksum>();
}

auto Endpoints::getLSPdatetime() const -> decltype(api::rest::LSPdatetime::Get::Response::_LSPdatetime)
{
  return m_sopasClient->readVariable<api::rest::LSPdatetime>()._LSPdatetime;
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

auto Endpoints::getOrderNumber() const -> decltype(api::rest::OrderNumber::Get::Response::_OrderNumber)
{
  return m_sopasClient->readVariable<api::rest::OrderNumber>()._OrderNumber;
}

auto Endpoints::getOutputState() const -> api::rest::OutputState::Get::Response
{
  return m_sopasClient->readVariable<api::rest::OutputState>();
}

auto Endpoints::getParticleFilter() const -> api::rest::particleFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::particleFilter>();
}

auto Endpoints::getPerformanceProfileNumber() const -> decltype(api::rest::PerformanceProfileNumber::Get::Response::_PerformanceProfileNumber)
{
  return m_sopasClient->readVariable<api::rest::PerformanceProfileNumber>()._PerformanceProfileNumber;
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

auto Endpoints::getRosPointCloud2Content() const -> api::rest::rosPointCloud2Content::Get::Response
{
  return m_sopasClient->readVariable<api::rest::rosPointCloud2Content>();
}

auto Endpoints::getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate)
{
  return m_sopasClient->readVariable<api::rest::SCdevicestate>()._SCdevicestate;
}

auto Endpoints::getScanConfig() const -> api::rest::ScanConfig::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ScanConfig>();
}

auto Endpoints::getSensitivityMode() const -> decltype(api::rest::SensitivityMode::Get::Response::_SensitivityMode)
{
  return m_sopasClient->readVariable<api::rest::SensitivityMode>()._SensitivityMode;
}

auto Endpoints::getSensorPosition() const -> api::rest::SensorPosition::Get::Response
{
  return m_sopasClient->readVariable<api::rest::SensorPosition>();
}

auto Endpoints::getSerialNumber() const -> decltype(api::rest::SerialNumber::Get::Response::_SerialNumber)
{
  return m_sopasClient->readVariable<api::rest::SerialNumber>()._SerialNumber;
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

auto Endpoints::getTreatBlockedSectorsAsErrorSectors() const -> decltype(api::rest::treatBlockedSectorsAsErrorSectors::Get::Response::_treatBlockedSectorsAsErrorSectors)
{
  return m_sopasClient->readVariable<api::rest::treatBlockedSectorsAsErrorSectors>()._treatBlockedSectorsAsErrorSectors;
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

void Endpoints::setAmbientPixelCountVertical(decltype(api::rest::ambientPixelCountVertical::Post::Request::_ambientPixelCountVertical) const& value) const
{
  m_sopasClient->writeVariable<api::rest::ambientPixelCountVertical>(api::rest::ambientPixelCountVertical::Post::Request{value});
}

void Endpoints::setAngleRangeFocusFilter(api::rest::angleRangeFocusFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::angleRangeFocusFilter>(request);
}

void Endpoints::setAutoStartMeasure(decltype(api::rest::AutoStartMeasure::Post::Request::_AutoStartMeasure) const& value) const
{
  m_sopasClient->writeVariable<api::rest::AutoStartMeasure>(api::rest::AutoStartMeasure::Post::Request{value});
}

void Endpoints::setBloomingFilter(api::rest::bloomingFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::bloomingFilter>(request);
}

auto Endpoints::setCertificateBundle(api::rest::setCertificateBundle::Post::Request const& request) const -> api::rest::setCertificateBundle::Post::Response
{
  return m_sopasClient->invokeMethod<api::rest::setCertificateBundle>(request);
}

void Endpoints::setCompactTelegramType6Content(api::rest::compactTelegramType6Content::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::compactTelegramType6Content>(request);
}

void Endpoints::setContaminationConfig(api::rest::ContaminationConfig::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::ContaminationConfig>(request);
}

void Endpoints::setDataOutputMode(decltype(api::rest::dataOutputMode::Post::Request::_dataOutputMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::dataOutputMode>(api::rest::dataOutputMode::Post::Request{value});
}

auto Endpoints::setDateTimeUTC(decltype(api::rest::setDateTimeUTC::Post::Request::_DateTime) const& value) const -> decltype(api::rest::setDateTimeUTC::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::setDateTimeUTC>(api::rest::setDateTimeUTC::Post::Request{value})._ErrorCode;
}

void Endpoints::setEnableHighPrecisionMode(decltype(api::rest::enableHighPrecisionMode::Post::Request::_enableHighPrecisionMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::enableHighPrecisionMode>(api::rest::enableHighPrecisionMode::Post::Request{value});
}

void Endpoints::setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAddressingMode>(api::rest::EtherAddressingMode::Post::Request{value});
}

void Endpoints::setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAuxEnabled>(api::rest::EtherAuxEnabled::Post::Request{value});
}

void Endpoints::setEtherCoLaScanMode(decltype(api::rest::EtherCoLaScanMode::Post::Request::_EtherCoLaScanMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherCoLaScanMode>(api::rest::EtherCoLaScanMode::Post::Request{value});
}

void Endpoints::setEtherDHCPFallback(decltype(api::rest::EtherDHCPFallback::Post::Request::_EtherDHCPFallback) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherDHCPFallback>(api::rest::EtherDHCPFallback::Post::Request{value});
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

void Endpoints::setFREchoFilter(decltype(api::rest::FREchoFilter::Post::Request::_FREchoFilter) const& value) const
{
  m_sopasClient->writeVariable<api::rest::FREchoFilter>(api::rest::FREchoFilter::Post::Request{value});
}

auto Endpoints::setFieldEvaluationConfiguration(api::rest::SetFieldEvaluationConfiguration::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationConfiguration::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::SetFieldEvaluationConfiguration>(request)._ErrorCode;
}

auto Endpoints::setFieldEvaluationContour(api::rest::SetFieldEvaluationContour::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationContour::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::SetFieldEvaluationContour>(request)._ErrorCode;
}

void Endpoints::setHorizontalFieldOfViewCenterAngle(decltype(api::rest::horizontalFieldOfViewCenterAngle::Post::Request::_horizontalFieldOfViewCenterAngle) const& value) const
{
  m_sopasClient->writeVariable<api::rest::horizontalFieldOfViewCenterAngle>(api::rest::horizontalFieldOfViewCenterAngle::Post::Request{value});
}

void Endpoints::setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LEDEnable>(api::rest::LEDEnable::Post::Request{value});
}

void Endpoints::setLFPintervalFilter(api::rest::LFPintervalFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::LFPintervalFilter>(request);
}

void Endpoints::setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LocationName>(api::rest::LocationName::Post::Request{value});
}

auto Endpoints::setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success)
{
  return m_sopasClient->invokeMethod<api::rest::SetOutput>(request)._Success;
}

void Endpoints::setParticleFilter(api::rest::particleFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::particleFilter>(request);
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

void Endpoints::setRosPointCloud2Content(api::rest::rosPointCloud2Content::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::rosPointCloud2Content>(request);
}

auto Endpoints::setScanConfigList(decltype(api::rest::SetScanConfigList::Post::Request::_ScanConfigList) const& value) const -> decltype(api::rest::SetScanConfigList::Post::Response::_eScanConfigError)
{
  return m_sopasClient->invokeMethod<api::rest::SetScanConfigList>(api::rest::SetScanConfigList::Post::Request{value})._eScanConfigError;
}

void Endpoints::setSensitivityMode(decltype(api::rest::SensitivityMode::Post::Request::_SensitivityMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::SensitivityMode>(api::rest::SensitivityMode::Post::Request{value});
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

void Endpoints::setTreatBlockedSectorsAsErrorSectors(decltype(api::rest::treatBlockedSectorsAsErrorSectors::Post::Request::_treatBlockedSectorsAsErrorSectors) const& value) const
{
  m_sopasClient->writeVariable<api::rest::treatBlockedSectorsAsErrorSectors>(api::rest::treatBlockedSectorsAsErrorSectors::Post::Request{value});
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

} // namespace sick::multiScan200::v1_1_0
