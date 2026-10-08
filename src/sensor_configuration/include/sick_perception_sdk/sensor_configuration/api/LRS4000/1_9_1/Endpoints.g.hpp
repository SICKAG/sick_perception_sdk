/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <string>

namespace sick {
class SopasClient;
} // namespace sick

namespace sick::LRS4000::v1_9_1 {

/**
 * @brief Typed access to all documented REST endpoints of this device/version.
 *
 * Each method forwards to the SopasClient engine. The nlohmann/json dependency is kept private
 * to the SDK library build, so including this header does not pull in nlohmann/json.
 */
class SDK_EXPORT Endpoints
{
public:
  explicit Endpoints(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);

  auto activateEvaluationGroup(decltype(api::rest::ActivateEvaluationGroup::Post::Request::_List) const& value) const -> decltype(api::rest::ActivateEvaluationGroup::Post::Response::_Success);
  auto changePassword(api::rest::changePassword::Post::Request const& request) const -> decltype(api::rest::changePassword::Post::Response::_result);
  auto doDiagnosisDump(api::rest::DoDiagnosisDump::Post::Request const& request) const -> decltype(api::rest::DoDiagnosisDump::Post::Response::_Successfull);
  void enableInertialMeasurementUnit(decltype(api::rest::EnableInertialMeasurementUnit::Post::Request::_EnableInertialMeasurementUnit) const& value) const;
  void encResolution(decltype(api::rest::EncResolution::Post::Request::_EncResolution) const& value) const;
  void encSetting(decltype(api::rest::EncSetting::Post::Request::_EncSetting) const& value) const;
  void encoderRotation(api::rest::EncoderRotation::Post::Request const& request) const;
  void encoderTransformationType(decltype(api::rest::EncoderTransformationType::Post::Request::_EncoderTransformationType) const& value) const;
  void encoderTranslation(api::rest::EncoderTranslation::Post::Request const& request) const;
  void etherColaTransmitTimeout(decltype(api::rest::EtherColaTransmitTimeout::Post::Request::_EtherColaTransmitTimeout) const& value) const;
  void ethernetUpdate() const;
  void findMe(decltype(api::rest::FindMe::Post::Request::_uiDuration) const& value) const;
  auto getActualEncSpeed() const -> decltype(api::rest::ActualEncSpeed::Get::Response::_ActualEncSpeed);
  void getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const;
  auto getContaminationActiveSectors() const -> decltype(api::rest::ContaminationActiveSectors::Get::Response::_ContaminationActiveSectors);
  auto getContaminationConfig() const -> api::rest::ContaminationConfig::Get::Response;
  auto getContaminationData() const -> decltype(api::rest::ContaminationData::Get::Response::_ContaminationData);
  auto getContaminationResult() const -> api::rest::ContaminationResult::Get::Response;
  auto getCurrentTempDev() const -> decltype(api::rest::CurrentTempDev::Get::Response::_CurrentTempDev);
  auto getDailyOpHours() const -> decltype(api::rest::DailyOpHours::Get::Response::_DailyOpHours);
  auto getDataOutputRange() const -> api::rest::DataOutputRange::Get::Response;
  auto getDateTime() const -> decltype(api::rest::DateTime::Get::Response::_DateTime);
  auto getDeviceIdent() const -> api::rest::DeviceIdent::Get::Response;
  auto getDeviceStatus() const -> decltype(api::rest::DeviceStatus::Get::Response::_DeviceStatus);
  auto getDeviceTime() const -> decltype(api::rest::DeviceTime::Get::Response::_DeviceTime);
  auto getDeviceType() const -> decltype(api::rest::DeviceType::Get::Response::_DeviceType);
  auto getDiagnosisDumpInfo() const -> api::rest::GetDiagnosisDumpInfo::Post::Response;
  auto getEnableColaScan() const -> decltype(api::rest::EnableColaScan::Get::Response::_EnableColaScan);
  auto getEnableDetectionHistory() const -> decltype(api::rest::EnableDetectionHistory::Get::Response::_EnableDetectionHistory);
  auto getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode);
  auto getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled);
  auto getEtherDHCPFallback() const -> decltype(api::rest::EtherDHCPFallback::Get::Response::_EtherDHCPFallback);
  auto getEtherIPAddress() const -> decltype(api::rest::EtherIPAddress::Get::Response::_EtherIPAddress);
  auto getEtherIPAddressDHCP() const -> decltype(api::rest::EtherIPAddressDHCP::Get::Response::_EtherIPAddressDHCP);
  auto getEtherIPGateAddress() const -> decltype(api::rest::EtherIPGateAddress::Get::Response::_EtherIPGateAddress);
  auto getEtherIPGateAddressDHCP() const -> decltype(api::rest::EtherIPGateAddressDHCP::Get::Response::_EtherIPGateAddressDHCP);
  auto getEtherIPMask() const -> decltype(api::rest::EtherIPMask::Get::Response::_EtherIPMask);
  auto getEtherIPMaskDHCP() const -> decltype(api::rest::EtherIPMaskDHCP::Get::Response::_EtherIPMaskDHCP);
  auto getEtherMACAddress() const -> decltype(api::rest::EtherMACAddress::Get::Response::_EtherMACAddress);
  auto getEvaluationsToLog() const -> decltype(api::rest::EvaluationsToLog::Get::Response::_EvaluationsToLog);
  auto getFREchoFilter() const -> decltype(api::rest::FREchoFilter::Get::Response::_FREchoFilter);
  auto getFieldEvaluationApplicationState() const -> decltype(api::rest::FieldEvaluationApplicationState::Get::Response::_FieldEvaluationApplicationState);
  auto getFieldEvaluationContour(decltype(api::rest::GetFieldEvaluationContour::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationContour::Post::Response::_Contour);
  auto getFieldEvaluationGroupState() const -> decltype(api::rest::FieldEvaluationGroupState::Get::Response::_FieldEvaluationGroupState);
  auto getFieldEvaluationResult() const -> decltype(api::rest::FieldEvaluationResult::Get::Response::_FieldEvaluationResult);
  auto getFirmwareVersion() const -> decltype(api::rest::FirmwareVersion::Get::Response::_FirmwareVersion);
  auto getInertialMeasurementUnit() const -> api::rest::InertialMeasurementUnit::Get::Response;
  auto getInputState() const -> api::rest::InputState::Get::Response;
  auto getLEDEnable() const -> decltype(api::rest::LEDEnable::Get::Response::_LEDEnable);
  auto getLFPmedianfilter() const -> api::rest::LFPmedianfilter::Get::Response;
  auto getLFPradialDistanceRangeFilter() const -> api::rest::LFPradialDistanceRangeFilter::Get::Response;
  auto getLastParaDate() const -> decltype(api::rest::LastParaDate::Get::Response::_LastParaDate);
  auto getLastParaTime() const -> decltype(api::rest::LastParaTime::Get::Response::_LastParaTime);
  auto getLocationName() const -> decltype(api::rest::LocationName::Get::Response::_LocationName);
  auto getMeanFilter() const -> api::rest::MeanFilter::Get::Response;
  auto getMotorSyncStatus() const -> decltype(api::rest::MotorSyncStatus::Get::Response::_MotorSyncStatus);
  auto getOpHours() const -> decltype(api::rest::OpHours::Get::Response::_OpHours);
  auto getOrderNumber() const -> decltype(api::rest::OrderNumber::Get::Response::_OrderNumber);
  auto getOutputState() const -> api::rest::OutputState::Get::Response;
  auto getParticleFilter() const -> api::rest::ParticleFilter::Get::Response;
  auto getPortConfiguration() const -> decltype(api::rest::PortConfiguration::Get::Response::_PortConfiguration);
  auto getPortState() const -> api::rest::PortState::Get::Response;
  auto getPowerOnCnt() const -> decltype(api::rest::PowerOnCnt::Get::Response::_PowerOnCnt);
  auto getRotationOffset() const -> api::rest::RotationOffset::Get::Response;
  auto getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate);
  auto getScanConfig() const -> api::rest::ScanConfig::Get::Response;
  auto getScanDataFormat() const -> decltype(api::rest::ScanDataFormat::Get::Response::_ScanDataFormat);
  auto getScanDataScaleFactor() const -> decltype(api::rest::ScanDataScaleFactor::Get::Response::_ScanDataScaleFactor);
  auto getSensitivityMode() const -> decltype(api::rest::SensitivityMode::Get::Response::_SensitivityMode);
  auto getSerialNumber() const -> decltype(api::rest::SerialNumber::Get::Response::_SerialNumber);
  auto getTSCRole() const -> decltype(api::rest::TSCRole::Get::Response::_TSCRole);
  auto getTSCTCSrvAddr() const -> decltype(api::rest::TSCTCSrvAddr::Get::Response::_TSCTCSrvAddr);
  auto getTSCTCtimezone() const -> decltype(api::rest::TSCTCtimezone::Get::Response::_TSCTCtimezone);
  auto getTSCTCupdatetime() const -> decltype(api::rest::TSCTCupdatetime::Get::Response::_TSCTCupdatetime);
  void loadApplicationDefaults() const;
  void loadFactoryDefaults() const;
  auto mResetOutputCounter() const -> decltype(api::rest::mResetOutputCounter::Post::Response::_ErrorCode);
  auto mSetDateTime(decltype(api::rest::mSetDateTime::Post::Request::_DateTime) const& value) const -> decltype(api::rest::mSetDateTime::Post::Response::_ErrorCode);
  auto mStandby() const -> decltype(api::rest::mStandby::Post::Response::_ErrorCode);
  auto mStartMeasure() const -> decltype(api::rest::mStartMeasure::Post::Response::_ErrorCode);
  void rebootDevice() const;
  void resetDetectionHistory() const;
  void scanMergeTrigger(decltype(api::rest::ScanMergeTrigger::Post::Request::_ScanMergeTrigger) const& value) const;
  void scanMergerEnabled(decltype(api::rest::ScanMergerEnabled::Post::Request::_ScanMergerEnabled) const& value) const;
  void scanMergerSource(decltype(api::rest::ScanMergerSource::Post::Request::_ScanMergerSource) const& value) const;
  void setContaminationConfig(api::rest::ContaminationConfig::Post::Request const& request) const;
  void setDataOutputRange(api::rest::DataOutputRange::Post::Request const& request) const;
  void setEnableColaScan(decltype(api::rest::EnableColaScan::Post::Request::_EnableColaScan) const& value) const;
  void setEnableDetectionHistory(decltype(api::rest::EnableDetectionHistory::Post::Request::_EnableDetectionHistory) const& value) const;
  void setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const;
  void setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const;
  void setEtherDHCPFallback(decltype(api::rest::EtherDHCPFallback::Post::Request::_EtherDHCPFallback) const& value) const;
  void setEtherIPAddress(decltype(api::rest::EtherIPAddress::Post::Request::_EtherIPAddress) const& value) const;
  void setEtherIPGateAddress(decltype(api::rest::EtherIPGateAddress::Post::Request::_EtherIPGateAddress) const& value) const;
  void setEtherIPMask(decltype(api::rest::EtherIPMask::Post::Request::_EtherIPMask) const& value) const;
  void setEvaluationsToLog(decltype(api::rest::EvaluationsToLog::Post::Request::_EvaluationsToLog) const& value) const;
  void setFREchoFilter(decltype(api::rest::FREchoFilter::Post::Request::_FREchoFilter) const& value) const;
  auto setFieldEvaluationContour(api::rest::SetFieldEvaluationContour::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationContour::Post::Response::_ErrorCode);
  void setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const;
  void setLFPmedianfilter(api::rest::LFPmedianfilter::Post::Request const& request) const;
  void setLFPradialDistanceRangeFilter(api::rest::LFPradialDistanceRangeFilter::Post::Request const& request) const;
  void setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const;
  void setMeanFilter(api::rest::MeanFilter::Post::Request const& request) const;
  auto setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success);
  void setParticleFilter(api::rest::ParticleFilter::Post::Request const& request) const;
  auto setPassword(api::rest::SetPassword::Post::Request const& request) const -> decltype(api::rest::SetPassword::Post::Response::_bSuccess);
  void setPortConfiguration(decltype(api::rest::PortConfiguration::Post::Request::_PortConfiguration) const& value) const;
  void setRotationOffset(api::rest::RotationOffset::Post::Request const& request) const;
  auto setScanConfigList(decltype(api::rest::SetScanConfigList::Post::Request::_ScanConfigList) const& value) const -> decltype(api::rest::SetScanConfigList::Post::Response::_eScanConfigError);
  void setScanDataFormat(decltype(api::rest::ScanDataFormat::Post::Request::_ScanDataFormat) const& value) const;
  void setScanDataScaleFactor(decltype(api::rest::ScanDataScaleFactor::Post::Request::_ScanDataScaleFactor) const& value) const;
  void setSensitivityMode(decltype(api::rest::SensitivityMode::Post::Request::_SensitivityMode) const& value) const;
  void setTSCRole(decltype(api::rest::TSCRole::Post::Request::_TSCRole) const& value) const;
  void setTSCTCSrvAddr(decltype(api::rest::TSCTCSrvAddr::Post::Request::_TSCTCSrvAddr) const& value) const;
  void setTSCTCtimezone(decltype(api::rest::TSCTCtimezone::Post::Request::_TSCTCtimezone) const& value) const;
  void setTSCTCupdatetime(decltype(api::rest::TSCTCupdatetime::Post::Request::_TSCTCupdatetime) const& value) const;
  void setWebserverEnabled(decltype(api::rest::SetWebserverEnabled::Post::Request::_Enable) const& value) const;
  void softReset(decltype(api::rest::SoftReset::Post::Request::_ProcessorNbr) const& value) const;
  void startScanMerge() const;
  void startTeachIn() const;
  void stopScanMerge() const;
  void stopTeachIn() const;
  void syncMode(decltype(api::rest::SyncMode::Post::Request::_SyncMode) const& value) const;
  void syncPhase(decltype(api::rest::SyncPhase::Post::Request::_SyncPhase) const& value) const;
  auto writeEeprom() const -> decltype(api::rest::WriteEeprom::Post::Response::_Success);

protected:
  std::unique_ptr<SopasClient> m_sopasClient;
};

} // namespace sick::LRS4000::v1_9_1
