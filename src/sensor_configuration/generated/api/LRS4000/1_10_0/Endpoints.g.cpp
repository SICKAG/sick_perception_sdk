/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.cpp Generated Endpoints implementation.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/Endpoints.g.hpp>

#include <sick_perception_sdk/sensor_configuration/SopasClientImpl.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <utility>

namespace sick::LRS4000::v1_10_0 {

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

auto Endpoints::doDiagnosisDump(api::rest::DoDiagnosisDump::Post::Request const& request) const -> decltype(api::rest::DoDiagnosisDump::Post::Response::_Successfull)
{
  return m_sopasClient->invokeMethod<api::rest::DoDiagnosisDump>(request)._Successfull;
}

void Endpoints::enableInertialMeasurementUnit(decltype(api::rest::EnableInertialMeasurementUnit::Post::Request::_EnableInertialMeasurementUnit) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EnableInertialMeasurementUnit>(api::rest::EnableInertialMeasurementUnit::Post::Request{value});
}

void Endpoints::encResolution(decltype(api::rest::EncResolution::Post::Request::_EncResolution) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EncResolution>(api::rest::EncResolution::Post::Request{value});
}

void Endpoints::encSetting(decltype(api::rest::EncSetting::Post::Request::_EncSetting) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EncSetting>(api::rest::EncSetting::Post::Request{value});
}

void Endpoints::encoderRotation(api::rest::EncoderRotation::Post::Request const& request) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EncoderRotation>(request);
}

void Endpoints::encoderTransformationType(decltype(api::rest::EncoderTransformationType::Post::Request::_EncoderTransformationType) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EncoderTransformationType>(api::rest::EncoderTransformationType::Post::Request{value});
}

void Endpoints::encoderTranslation(api::rest::EncoderTranslation::Post::Request const& request) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EncoderTranslation>(request);
}

void Endpoints::etherColaTransmitTimeout(decltype(api::rest::EtherColaTransmitTimeout::Post::Request::_EtherColaTransmitTimeout) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::EtherColaTransmitTimeout>(api::rest::EtherColaTransmitTimeout::Post::Request{value});
}

void Endpoints::ethernetUpdate() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::EthernetUpdate>();
}

void Endpoints::findMe(decltype(api::rest::FindMe::Post::Request::_uiDuration) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::FindMe>(api::rest::FindMe::Post::Request{value});
}

auto Endpoints::getActualEncSpeed() const -> decltype(api::rest::ActualEncSpeed::Get::Response::_ActualEncSpeed)
{
  return m_sopasClient->readVariable<api::rest::ActualEncSpeed>()._ActualEncSpeed;
}

auto Endpoints::getCertificateBundleInfo() const -> api::rest::certificateBundleInfo::Get::Response
{
  return m_sopasClient->readVariable<api::rest::certificateBundleInfo>();
}

void Endpoints::getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::getChallenge>(api::rest::getChallenge::Post::Request{value});
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

auto Endpoints::getCurrentTempDev() const -> decltype(api::rest::CurrentTempDev::Get::Response::_CurrentTempDev)
{
  return m_sopasClient->readVariable<api::rest::CurrentTempDev>()._CurrentTempDev;
}

auto Endpoints::getDailyOpHours() const -> decltype(api::rest::DailyOpHours::Get::Response::_DailyOpHours)
{
  return m_sopasClient->readVariable<api::rest::DailyOpHours>()._DailyOpHours;
}

auto Endpoints::getDataOutputRange() const -> api::rest::DataOutputRange::Get::Response
{
  return m_sopasClient->readVariable<api::rest::DataOutputRange>();
}

auto Endpoints::getDateTime() const -> decltype(api::rest::DateTime::Get::Response::_DateTime)
{
  return m_sopasClient->readVariable<api::rest::DateTime>()._DateTime;
}

auto Endpoints::getDeviceIdent() const -> api::rest::DeviceIdent::Get::Response
{
  return m_sopasClient->readVariable<api::rest::DeviceIdent>();
}

auto Endpoints::getDeviceStatus() const -> decltype(api::rest::DeviceStatus::Get::Response::_DeviceStatus)
{
  return m_sopasClient->readVariable<api::rest::DeviceStatus>()._DeviceStatus;
}

auto Endpoints::getDeviceTime() const -> decltype(api::rest::DeviceTime::Get::Response::_DeviceTime)
{
  return m_sopasClient->readVariable<api::rest::DeviceTime>()._DeviceTime;
}

auto Endpoints::getDeviceType() const -> decltype(api::rest::DeviceType::Get::Response::_DeviceType)
{
  return m_sopasClient->readVariable<api::rest::DeviceType>()._DeviceType;
}

auto Endpoints::getDiagnosisDumpInfo() const -> api::rest::GetDiagnosisDumpInfo::Post::Response
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::GetDiagnosisDumpInfo>();
}

auto Endpoints::getEnableColaScan() const -> decltype(api::rest::EnableColaScan::Get::Response::_EnableColaScan)
{
  return m_sopasClient->readVariable<api::rest::EnableColaScan>()._EnableColaScan;
}

auto Endpoints::getEnableDetectionHistory() const -> decltype(api::rest::EnableDetectionHistory::Get::Response::_EnableDetectionHistory)
{
  return m_sopasClient->readVariable<api::rest::EnableDetectionHistory>()._EnableDetectionHistory;
}

auto Endpoints::getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode)
{
  return m_sopasClient->readVariable<api::rest::EtherAddressingMode>()._EtherAddressingMode;
}

auto Endpoints::getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled)
{
  return m_sopasClient->readVariable<api::rest::EtherAuxEnabled>()._EtherAuxEnabled;
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

auto Endpoints::getEvaluationGroupType() const -> decltype(api::rest::EvaluationGroupType::Get::Response::_EvaluationGroupType)
{
  return m_sopasClient->readVariable<api::rest::EvaluationGroupType>()._EvaluationGroupType;
}

auto Endpoints::getEvaluationsToLog() const -> decltype(api::rest::EvaluationsToLog::Get::Response::_EvaluationsToLog)
{
  return m_sopasClient->readVariable<api::rest::EvaluationsToLog>()._EvaluationsToLog;
}

auto Endpoints::getFREchoFilter() const -> decltype(api::rest::FREchoFilter::Get::Response::_FREchoFilter)
{
  return m_sopasClient->readVariable<api::rest::FREchoFilter>()._FREchoFilter;
}

auto Endpoints::getFieldEvaluationApplicationState() const -> decltype(api::rest::FieldEvaluationApplicationState::Get::Response::_FieldEvaluationApplicationState)
{
  return m_sopasClient->readVariable<api::rest::FieldEvaluationApplicationState>()._FieldEvaluationApplicationState;
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

auto Endpoints::getLFPmedianfilter() const -> api::rest::LFPmedianfilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFPmedianfilter>();
}

auto Endpoints::getLFPradialDistanceRangeFilter() const -> api::rest::LFPradialDistanceRangeFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::LFPradialDistanceRangeFilter>();
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

auto Endpoints::getMeanFilter() const -> api::rest::MeanFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::MeanFilter>();
}

auto Endpoints::getMotorSyncStatus() const -> decltype(api::rest::MotorSyncStatus::Get::Response::_MotorSyncStatus)
{
  return m_sopasClient->readVariable<api::rest::MotorSyncStatus>()._MotorSyncStatus;
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

auto Endpoints::getParticleFilter() const -> api::rest::ParticleFilter::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ParticleFilter>();
}

auto Endpoints::getPerpendicularDistanceResult() const -> api::rest::perpendicularDistanceResult::Get::Response
{
  return m_sopasClient->readVariable<api::rest::perpendicularDistanceResult>();
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

auto Endpoints::getRotationOffset() const -> api::rest::RotationOffset::Get::Response
{
  return m_sopasClient->readVariable<api::rest::RotationOffset>();
}

auto Endpoints::getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate)
{
  return m_sopasClient->readVariable<api::rest::SCdevicestate>()._SCdevicestate;
}

auto Endpoints::getScanConfig() const -> api::rest::ScanConfig::Get::Response
{
  return m_sopasClient->readVariable<api::rest::ScanConfig>();
}

auto Endpoints::getScanDataFormat() const -> decltype(api::rest::ScanDataFormat::Get::Response::_ScanDataFormat)
{
  return m_sopasClient->readVariable<api::rest::ScanDataFormat>()._ScanDataFormat;
}

auto Endpoints::getScanDataScaleFactor() const -> decltype(api::rest::ScanDataScaleFactor::Get::Response::_ScanDataScaleFactor)
{
  return m_sopasClient->readVariable<api::rest::ScanDataScaleFactor>()._ScanDataScaleFactor;
}

auto Endpoints::getSensitivityMode() const -> decltype(api::rest::SensitivityMode::Get::Response::_SensitivityMode)
{
  return m_sopasClient->readVariable<api::rest::SensitivityMode>()._SensitivityMode;
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

auto Endpoints::mSetDateTime(decltype(api::rest::mSetDateTime::Post::Request::_DateTime) const& value) const -> decltype(api::rest::mSetDateTime::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::mSetDateTime>(api::rest::mSetDateTime::Post::Request{value})._ErrorCode;
}

auto Endpoints::mStandby() const -> decltype(api::rest::mStandby::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mStandby>()._ErrorCode;
}

auto Endpoints::mStartMeasure() const -> decltype(api::rest::mStartMeasure::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::mStartMeasure>()._ErrorCode;
}

void Endpoints::rebootDevice() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::RebootDevice>();
}

void Endpoints::resetDetectionHistory() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::ResetDetectionHistory>();
}

void Endpoints::scanMergeTrigger(decltype(api::rest::ScanMergeTrigger::Post::Request::_ScanMergeTrigger) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::ScanMergeTrigger>(api::rest::ScanMergeTrigger::Post::Request{value});
}

void Endpoints::scanMergerEnabled(decltype(api::rest::ScanMergerEnabled::Post::Request::_ScanMergerEnabled) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::ScanMergerEnabled>(api::rest::ScanMergerEnabled::Post::Request{value});
}

void Endpoints::scanMergerSource(decltype(api::rest::ScanMergerSource::Post::Request::_ScanMergerSource) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::ScanMergerSource>(api::rest::ScanMergerSource::Post::Request{value});
}

void Endpoints::setContaminationConfig(api::rest::ContaminationConfig::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::ContaminationConfig>(request);
}

void Endpoints::setDataOutputRange(api::rest::DataOutputRange::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::DataOutputRange>(request);
}

void Endpoints::setEnableColaScan(decltype(api::rest::EnableColaScan::Post::Request::_EnableColaScan) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EnableColaScan>(api::rest::EnableColaScan::Post::Request{value});
}

void Endpoints::setEnableDetectionHistory(decltype(api::rest::EnableDetectionHistory::Post::Request::_EnableDetectionHistory) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EnableDetectionHistory>(api::rest::EnableDetectionHistory::Post::Request{value});
}

void Endpoints::setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAddressingMode>(api::rest::EtherAddressingMode::Post::Request{value});
}

void Endpoints::setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EtherAuxEnabled>(api::rest::EtherAuxEnabled::Post::Request{value});
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

void Endpoints::setEvaluationGroupType(decltype(api::rest::EvaluationGroupType::Post::Request::_EvaluationGroupType) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EvaluationGroupType>(api::rest::EvaluationGroupType::Post::Request{value});
}

void Endpoints::setEvaluationsToLog(decltype(api::rest::EvaluationsToLog::Post::Request::_EvaluationsToLog) const& value) const
{
  m_sopasClient->writeVariable<api::rest::EvaluationsToLog>(api::rest::EvaluationsToLog::Post::Request{value});
}

void Endpoints::setFREchoFilter(decltype(api::rest::FREchoFilter::Post::Request::_FREchoFilter) const& value) const
{
  m_sopasClient->writeVariable<api::rest::FREchoFilter>(api::rest::FREchoFilter::Post::Request{value});
}

auto Endpoints::setFieldEvaluationContour(api::rest::SetFieldEvaluationContour::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationContour::Post::Response::_ErrorCode)
{
  return m_sopasClient->invokeMethod<api::rest::SetFieldEvaluationContour>(request)._ErrorCode;
}

void Endpoints::setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LEDEnable>(api::rest::LEDEnable::Post::Request{value});
}

void Endpoints::setLFPmedianfilter(api::rest::LFPmedianfilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::LFPmedianfilter>(request);
}

void Endpoints::setLFPradialDistanceRangeFilter(api::rest::LFPradialDistanceRangeFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::LFPradialDistanceRangeFilter>(request);
}

void Endpoints::setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const
{
  m_sopasClient->writeVariable<api::rest::LocationName>(api::rest::LocationName::Post::Request{value});
}

void Endpoints::setMeanFilter(api::rest::MeanFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::MeanFilter>(request);
}

auto Endpoints::setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success)
{
  return m_sopasClient->invokeMethod<api::rest::SetOutput>(request)._Success;
}

void Endpoints::setParticleFilter(api::rest::ParticleFilter::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::ParticleFilter>(request);
}

auto Endpoints::setPassword(api::rest::SetPassword::Post::Request const& request) const -> decltype(api::rest::SetPassword::Post::Response::_bSuccess)
{
  return m_sopasClient->invokeMethod<api::rest::SetPassword>(request)._bSuccess;
}

void Endpoints::setPortConfiguration(decltype(api::rest::PortConfiguration::Post::Request::_PortConfiguration) const& value) const
{
  m_sopasClient->writeVariable<api::rest::PortConfiguration>(api::rest::PortConfiguration::Post::Request{value});
}

void Endpoints::setRotationOffset(api::rest::RotationOffset::Post::Request const& request) const
{
  m_sopasClient->writeVariable<api::rest::RotationOffset>(request);
}

auto Endpoints::setScanConfigList(decltype(api::rest::SetScanConfigList::Post::Request::_ScanConfigList) const& value) const -> decltype(api::rest::SetScanConfigList::Post::Response::_eScanConfigError)
{
  return m_sopasClient->invokeMethod<api::rest::SetScanConfigList>(api::rest::SetScanConfigList::Post::Request{value})._eScanConfigError;
}

void Endpoints::setScanDataFormat(decltype(api::rest::ScanDataFormat::Post::Request::_ScanDataFormat) const& value) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataFormat>(api::rest::ScanDataFormat::Post::Request{value});
}

void Endpoints::setScanDataScaleFactor(decltype(api::rest::ScanDataScaleFactor::Post::Request::_ScanDataScaleFactor) const& value) const
{
  m_sopasClient->writeVariable<api::rest::ScanDataScaleFactor>(api::rest::ScanDataScaleFactor::Post::Request{value});
}

void Endpoints::setSensitivityMode(decltype(api::rest::SensitivityMode::Post::Request::_SensitivityMode) const& value) const
{
  m_sopasClient->writeVariable<api::rest::SensitivityMode>(api::rest::SensitivityMode::Post::Request{value});
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

void Endpoints::setWebserverEnabled(decltype(api::rest::SetWebserverEnabled::Post::Request::_Enable) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SetWebserverEnabled>(api::rest::SetWebserverEnabled::Post::Request{value});
}

void Endpoints::softReset(decltype(api::rest::SoftReset::Post::Request::_ProcessorNbr) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SoftReset>(api::rest::SoftReset::Post::Request{value});
}

void Endpoints::startScanMerge() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::StartScanMerge>();
}

void Endpoints::startTeachIn() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::StartTeachIn>();
}

void Endpoints::stopScanMerge() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::StopScanMerge>();
}

void Endpoints::stopTeachIn() const
{
  m_sopasClient->invokeMethodWithoutRequestAndResponse<api::rest::StopTeachIn>();
}

void Endpoints::syncMode(decltype(api::rest::SyncMode::Post::Request::_SyncMode) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SyncMode>(api::rest::SyncMode::Post::Request{value});
}

void Endpoints::syncPhase(decltype(api::rest::SyncPhase::Post::Request::_SyncPhase) const& value) const
{
  m_sopasClient->invokeMethodWithoutResponse<api::rest::SyncPhase>(api::rest::SyncPhase::Post::Request{value});
}

auto Endpoints::writeEeprom() const -> decltype(api::rest::WriteEeprom::Post::Response::_Success)
{
  return m_sopasClient->invokeMethodWithoutRequest<api::rest::WriteEeprom>()._Success;
}

} // namespace sick::LRS4000::v1_10_0
