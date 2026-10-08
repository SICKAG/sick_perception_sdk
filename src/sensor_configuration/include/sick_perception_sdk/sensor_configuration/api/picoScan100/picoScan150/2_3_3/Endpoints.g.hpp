/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150/2_3_3.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <string>

namespace sick {
class SopasClient;
} // namespace sick

namespace sick::picoScan150::v2_3_3 {

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
  void checkCredentials() const;
  auto createParameterBackup(decltype(api::rest::CreateParameterBackup::Post::Request::_Passphrase) const& value) const -> decltype(api::rest::CreateParameterBackup::Post::Response::_Result);
  auto createSessionToken() const -> api::rest::CreateSessionToken::Post::Response;
  auto doDiagnosisDump(api::rest::DoDiagnosisDump::Post::Request const& request) const -> decltype(api::rest::DoDiagnosisDump::Post::Response::_Successfull);
  auto enableLegacyUserLevel(api::rest::EnableLegacyUserLevel::Post::Request const& request) const -> decltype(api::rest::EnableLegacyUserLevel::Post::Response::_result);
  auto enableUserLevel(api::rest::EnableUserLevel::Post::Request const& request) const -> decltype(api::rest::EnableUserLevel::Post::Response::_result);
  void ethernetUpdate() const;
  void findMe(decltype(api::rest::FindMe::Post::Request::_uiDuration) const& value) const;
  auto getActualEncPosition1Enable() const -> decltype(api::rest::ActualEncPosition1Enable::Get::Response::_ActualEncPosition1Enable);
  auto getActualEncPosition2Enable() const -> decltype(api::rest::ActualEncPosition2Enable::Get::Response::_ActualEncPosition2Enable);
  auto getAutoStartMeasure() const -> decltype(api::rest::AutoStartMeasure::Get::Response::_AutoStartMeasure);
  auto getCertificateBundleInfo() const -> api::rest::certificateBundleInfo::Get::Response;
  void getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const;
  auto getCompactTelegramType1Content() const -> api::rest::compactTelegramType1Content::Get::Response;
  auto getContaminationActiveSectors() const -> decltype(api::rest::ContaminationActiveSectors::Get::Response::_ContaminationActiveSectors);
  auto getContaminationConfig() const -> api::rest::ContaminationConfig::Get::Response;
  auto getContaminationData() const -> decltype(api::rest::ContaminationData::Get::Response::_ContaminationData);
  auto getContaminationResult() const -> api::rest::ContaminationResult::Get::Response;
  auto getCreateParameterBackupResult() const -> api::rest::CreateParameterBackupResult::Get::Response;
  auto getCurrentTempDev() const -> decltype(api::rest::CurrentTempDev::Get::Response::_CurrentTempDev);
  auto getDailyOpHours() const -> decltype(api::rest::DailyOpHours::Get::Response::_DailyOpHours);
  auto getDeviceIdent() const -> api::rest::DeviceIdent::Get::Response;
  auto getDeviceStatus() const -> decltype(api::rest::DeviceStatus::Get::Response::_DeviceStatus);
  auto getDeviceType() const -> decltype(api::rest::DeviceType::Get::Response::_DeviceType);
  auto getDiagnosisDumpInfo() const -> api::rest::GetDiagnosisDumpInfo::Post::Response;
  auto getEnableCloningPlug() const -> decltype(api::rest::enableCloningPlug::Get::Response::_enableCloningPlug);
  auto getEnableDetectionHistory() const -> decltype(api::rest::EnableDetectionHistory::Get::Response::_EnableDetectionHistory);
  auto getEnableLongRangeMode() const -> decltype(api::rest::EnableLongRangeMode::Get::Response::_EnableLongRangeMode);
  auto getEncResolution() const -> decltype(api::rest::EncResolution::Get::Response::_EncResolution);
  auto getEncSetting() const -> decltype(api::rest::EncSetting::Get::Response::_EncSetting);
  auto getEncoderDataEnable() const -> decltype(api::rest::EncoderDataEnable::Get::Response::_EncoderDataEnable);
  auto getEncoderDataEthSettings() const -> api::rest::EncoderDataEthSettings::Get::Response;
  auto getEncoderRotation() const -> api::rest::EncoderRotation::Get::Response;
  auto getEncoderTransformationType() const -> decltype(api::rest::EncoderTransformationType::Get::Response::_EncoderTransformationType);
  auto getEncoderTranslation() const -> api::rest::EncoderTranslation::Get::Response;
  auto getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode);
  auto getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled);
  auto getEtherAuxIPPort() const -> decltype(api::rest::EtherAuxIPPort::Get::Response::_EtherAuxIPPort);
  auto getEtherCoLaScanMode() const -> decltype(api::rest::EtherCoLaScanMode::Get::Response::_EtherCoLaScanMode);
  auto getEtherDHCPFallback() const -> decltype(api::rest::EtherDHCPFallback::Get::Response::_EtherDHCPFallback);
  auto getEtherHostIPPort() const -> decltype(api::rest::EtherHostIPPort::Get::Response::_EtherHostIPPort);
  auto getEtherIPAddress() const -> decltype(api::rest::EtherIPAddress::Get::Response::_EtherIPAddress);
  auto getEtherIPAddressDHCP() const -> decltype(api::rest::EtherIPAddressDHCP::Get::Response::_EtherIPAddressDHCP);
  auto getEtherIPGateAddress() const -> decltype(api::rest::EtherIPGateAddress::Get::Response::_EtherIPGateAddress);
  auto getEtherIPGateAddressDHCP() const -> decltype(api::rest::EtherIPGateAddressDHCP::Get::Response::_EtherIPGateAddressDHCP);
  auto getEtherIPMask() const -> decltype(api::rest::EtherIPMask::Get::Response::_EtherIPMask);
  auto getEtherIPMaskDHCP() const -> decltype(api::rest::EtherIPMaskDHCP::Get::Response::_EtherIPMaskDHCP);
  auto getEtherMACAddress() const -> decltype(api::rest::EtherMACAddress::Get::Response::_EtherMACAddress);
  auto getEtherSessionTimeout() const -> decltype(api::rest::EtherSessionTimeout::Get::Response::_EtherSessionTimeout);
  auto getEvaluationGroupType() const -> decltype(api::rest::EvaluationGroupType::Get::Response::_EvaluationGroupType);
  auto getEvaluationsToLog() const -> decltype(api::rest::EvaluationsToLog::Get::Response::_EvaluationsToLog);
  auto getFREchoFilter() const -> decltype(api::rest::FREchoFilter::Get::Response::_FREchoFilter);
  auto getFieldEvaluationContour(decltype(api::rest::GetFieldEvaluationContour::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationContour::Post::Response::_Contour);
  auto getFieldEvaluationGroupState() const -> decltype(api::rest::FieldEvaluationGroupState::Get::Response::_FieldEvaluationGroupState);
  auto getFieldEvaluationResult() const -> decltype(api::rest::FieldEvaluationResult::Get::Response::_FieldEvaluationResult);
  auto getFirmwareVersion() const -> decltype(api::rest::FirmwareVersion::Get::Response::_FirmwareVersion);
  auto getHttpsStatus() const -> api::rest::httpsStatus::Get::Response;
  auto getImuDataEnable() const -> decltype(api::rest::ImuDataEnable::Get::Response::_ImuDataEnable);
  auto getImuDataEthSettings() const -> api::rest::ImuDataEthSettings::Get::Response;
  auto getInertialMeasurementUnit() const -> api::rest::InertialMeasurementUnit::Get::Response;
  auto getInputState() const -> api::rest::InputState::Get::Response;
  auto getLEDEnable() const -> decltype(api::rest::LEDEnable::Get::Response::_LEDEnable);
  auto getLEDState() const -> decltype(api::rest::LEDState::Get::Response::_LEDState);
  auto getLFPangleRangeFilter() const -> api::rest::LFPangleRangeFilter::Get::Response;
  auto getLFPcubicareafilter() const -> api::rest::LFPcubicareafilter::Get::Response;
  auto getLFPintervalFilter() const -> api::rest::LFPintervalFilter::Get::Response;
  auto getLFPmovingAveragingFilter() const -> api::rest::LFPmovingAveragingFilter::Get::Response;
  auto getLFPparticle() const -> api::rest::LFPparticle::Get::Response;
  auto getLFPradialDistanceRangeFilter() const -> api::rest::LFPradialDistanceRangeFilter::Get::Response;
  auto getLFTchecksum() const -> api::rest::LFTchecksum::Get::Response;
  auto getLSPdatetime() const -> decltype(api::rest::LSPdatetime::Get::Response::_LSPdatetime);
  auto getLaserType() const -> decltype(api::rest::laserType::Get::Response::_laserType);
  auto getLastParaDate() const -> decltype(api::rest::LastParaDate::Get::Response::_LastParaDate);
  auto getLastParaTime() const -> decltype(api::rest::LastParaTime::Get::Response::_LastParaTime);
  auto getLocationName() const -> decltype(api::rest::LocationName::Get::Response::_LocationName);
  auto getMCSenseLevel() const -> decltype(api::rest::MCSenseLevel::Get::Response::_MCSenseLevel);
  auto getMergeSaving() const -> decltype(api::rest::MergeSaving::Get::Response::_MergeSaving);
  auto getOpHours() const -> decltype(api::rest::OpHours::Get::Response::_OpHours);
  auto getOrderNumber() const -> decltype(api::rest::OrderNumber::Get::Response::_OrderNumber);
  auto getOutputState() const -> api::rest::OutputState::Get::Response;
  auto getPerformanceProfileNumber() const -> decltype(api::rest::PerformanceProfileNumber::Get::Response::_PerformanceProfileNumber);
  auto getPerpendicularDistanceResult() const -> api::rest::perpendicularDistanceResult::Get::Response;
  auto getPortConfiguration() const -> decltype(api::rest::PortConfiguration::Get::Response::_PortConfiguration);
  auto getPortState() const -> api::rest::PortState::Get::Response;
  auto getPowerOnCnt() const -> decltype(api::rest::PowerOnCnt::Get::Response::_PowerOnCnt);
  auto getRestoreParameterBackupResult() const -> api::rest::RestoreParameterBackupResult::Get::Response;
  auto getRosDomainId() const -> decltype(api::rest::rosDomainId::Get::Response::_rosDomainId);
  auto getRosFrameId() const -> decltype(api::rest::rosFrameId::Get::Response::_rosFrameId);
  auto getRosNamespace() const -> decltype(api::rest::rosNamespace::Get::Response::_rosNamespace);
  auto getRosParentFrameId() const -> decltype(api::rest::rosParentFrameId::Get::Response::_rosParentFrameId);
  auto getRotationOffset() const -> api::rest::RotationOffset::Get::Response;
  auto getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate);
  auto getScanConfig() const -> api::rest::ScanConfig::Get::Response;
  auto getScanDataConfig() const -> api::rest::ScanDataConfig::Get::Response;
  auto getScanDataEnable() const -> decltype(api::rest::ScanDataEnable::Get::Response::_ScanDataEnable);
  auto getScanDataEthSettings() const -> api::rest::ScanDataEthSettings::Get::Response;
  auto getScanDataFormat() const -> decltype(api::rest::ScanDataFormat::Get::Response::_ScanDataFormat);
  auto getScanMergeTrigger() const -> decltype(api::rest::ScanMergeTrigger::Get::Response::_ScanMergeTrigger);
  auto getScanMergerEnabled() const -> decltype(api::rest::ScanMergerEnabled::Get::Response::_ScanMergerEnabled);
  auto getScanMergerSource() const -> decltype(api::rest::ScanMergerSource::Get::Response::_ScanMergerSource);
  auto getSensitivityMode() const -> decltype(api::rest::SensitivityMode::Get::Response::_SensitivityMode);
  auto getSensorPosition() const -> api::rest::SensorPosition::Get::Response;
  auto getSerialNumber() const -> decltype(api::rest::SerialNumber::Get::Response::_SerialNumber);
  auto getSipmType() const -> decltype(api::rest::sipmType::Get::Response::_sipmType);
  auto getTSCRole() const -> decltype(api::rest::TSCRole::Get::Response::_TSCRole);
  auto getTSCTCSrvAddr() const -> decltype(api::rest::TSCTCSrvAddr::Get::Response::_TSCTCSrvAddr);
  auto getTSCTCtimezone() const -> decltype(api::rest::TSCTCtimezone::Get::Response::_TSCTCtimezone);
  auto getTSCTCupdatetime() const -> decltype(api::rest::TSCTCupdatetime::Get::Response::_TSCTCupdatetime);
  auto getTemperatureAlarmConfiguration() const -> api::rest::temperatureAlarmConfiguration::Get::Response;
  auto getTemperatureAlarmStatus() const -> decltype(api::rest::temperatureAlarmStatus::Get::Response::_temperatureAlarmStatus);
  auto getTreatBlockedSectorsAsErrorSectors() const -> decltype(api::rest::treatBlockedSectorsAsErrorSectors::Get::Response::_treatBlockedSectorsAsErrorSectors);
  auto getUpdateState() const -> decltype(api::rest::UpdateState::Get::Response::_UpdateState);
  auto getWebserverEnabled() const -> decltype(api::rest::GetWebserverEnabled::Post::Response::_IsEnabled);
  auto lSPsetdatetime(decltype(api::rest::LSPsetdatetime::Post::Request::_DateTime) const& value) const -> decltype(api::rest::LSPsetdatetime::Post::Response::_ErrorCode);
  void loadApplicationDefaults() const;
  void loadFactoryDefaults() const;
  auto mResetEncoderIncrement() const -> decltype(api::rest::mResetEncoderIncrement::Post::Response::_ErrorCode);
  auto mResetOutputCounter() const -> decltype(api::rest::mResetOutputCounter::Post::Response::_ErrorCode);
  auto mStandby() const -> decltype(api::rest::mStandby::Post::Response::_ErrorCode);
  auto mStartMeasure() const -> decltype(api::rest::mStartMeasure::Post::Response::_ErrorCode);
  auto mStopMeasure() const -> decltype(api::rest::mStopMeasure::Post::Response::_ErrorCode);
  void rebootDevice() const;
  auto removeCertificateBundle() const -> api::rest::removeCertificateBundle::Post::Response;
  void resetDetectionHistory() const;
  void resetScanMergeView() const;
  auto restoreParameterBackup(api::rest::RestoreParameterBackup::Post::Request const& request) const -> decltype(api::rest::RestoreParameterBackup::Post::Response::_Result);
  void runFirmwareUpdate() const;
  void setActualEncPosition1Enable(decltype(api::rest::ActualEncPosition1Enable::Post::Request::_ActualEncPosition1Enable) const& value) const;
  void setActualEncPosition2Enable(decltype(api::rest::ActualEncPosition2Enable::Post::Request::_ActualEncPosition2Enable) const& value) const;
  void setAutoStartMeasure(decltype(api::rest::AutoStartMeasure::Post::Request::_AutoStartMeasure) const& value) const;
  auto setCertificateBundle(api::rest::setCertificateBundle::Post::Request const& request) const -> api::rest::setCertificateBundle::Post::Response;
  void setCompactTelegramType1Content(api::rest::compactTelegramType1Content::Post::Request const& request) const;
  void setContaminationConfig(api::rest::ContaminationConfig::Post::Request const& request) const;
  void setEnableCloningPlug(decltype(api::rest::enableCloningPlug::Post::Request::_enableCloningPlug) const& value) const;
  void setEnableDetectionHistory(decltype(api::rest::EnableDetectionHistory::Post::Request::_EnableDetectionHistory) const& value) const;
  void setEnableLongRangeMode(decltype(api::rest::EnableLongRangeMode::Post::Request::_EnableLongRangeMode) const& value) const;
  void setEncResolution(decltype(api::rest::EncResolution::Post::Request::_EncResolution) const& value) const;
  void setEncSetting(decltype(api::rest::EncSetting::Post::Request::_EncSetting) const& value) const;
  void setEncoderDataEnable(decltype(api::rest::EncoderDataEnable::Post::Request::_EncoderDataEnable) const& value) const;
  void setEncoderDataEthSettings(api::rest::EncoderDataEthSettings::Post::Request const& request) const;
  void setEncoderRotation(api::rest::EncoderRotation::Post::Request const& request) const;
  void setEncoderTransformationType(decltype(api::rest::EncoderTransformationType::Post::Request::_EncoderTransformationType) const& value) const;
  void setEncoderTranslation(api::rest::EncoderTranslation::Post::Request const& request) const;
  void setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const;
  void setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const;
  void setEtherAuxIPPort(decltype(api::rest::EtherAuxIPPort::Post::Request::_EtherAuxIPPort) const& value) const;
  void setEtherCoLaScanMode(decltype(api::rest::EtherCoLaScanMode::Post::Request::_EtherCoLaScanMode) const& value) const;
  void setEtherDHCPFallback(decltype(api::rest::EtherDHCPFallback::Post::Request::_EtherDHCPFallback) const& value) const;
  void setEtherHostIPPort(decltype(api::rest::EtherHostIPPort::Post::Request::_EtherHostIPPort) const& value) const;
  void setEtherIPAddress(decltype(api::rest::EtherIPAddress::Post::Request::_EtherIPAddress) const& value) const;
  void setEtherIPGateAddress(decltype(api::rest::EtherIPGateAddress::Post::Request::_EtherIPGateAddress) const& value) const;
  void setEtherIPMask(decltype(api::rest::EtherIPMask::Post::Request::_EtherIPMask) const& value) const;
  void setEtherSessionTimeout(decltype(api::rest::EtherSessionTimeout::Post::Request::_EtherSessionTimeout) const& value) const;
  void setEvaluationsToLog(decltype(api::rest::EvaluationsToLog::Post::Request::_EvaluationsToLog) const& value) const;
  void setFREchoFilter(decltype(api::rest::FREchoFilter::Post::Request::_FREchoFilter) const& value) const;
  auto setFieldEvaluationContour(api::rest::SetFieldEvaluationContour::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationContour::Post::Response::_ErrorCode);
  void setImuDataEnable(decltype(api::rest::ImuDataEnable::Post::Request::_ImuDataEnable) const& value) const;
  void setImuDataEthSettings(api::rest::ImuDataEthSettings::Post::Request const& request) const;
  void setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const;
  void setLFPangleRangeFilter(api::rest::LFPangleRangeFilter::Post::Request const& request) const;
  void setLFPcubicareafilter(api::rest::LFPcubicareafilter::Post::Request const& request) const;
  void setLFPintervalFilter(api::rest::LFPintervalFilter::Post::Request const& request) const;
  void setLFPmovingAveragingFilter(api::rest::LFPmovingAveragingFilter::Post::Request const& request) const;
  void setLFPparticle(api::rest::LFPparticle::Post::Request const& request) const;
  void setLFPradialDistanceRangeFilter(api::rest::LFPradialDistanceRangeFilter::Post::Request const& request) const;
  void setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const;
  void setMCSenseLevel(decltype(api::rest::MCSenseLevel::Post::Request::_MCSenseLevel) const& value) const;
  auto setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success);
  auto setPassword(api::rest::SetPassword::Post::Request const& request) const -> decltype(api::rest::SetPassword::Post::Response::_bSuccess);
  void setPerformanceProfileNumber(decltype(api::rest::PerformanceProfileNumber::Post::Request::_PerformanceProfileNumber) const& value) const;
  void setPortConfiguration(decltype(api::rest::PortConfiguration::Post::Request::_PortConfiguration) const& value) const;
  void setRosDomainId(decltype(api::rest::rosDomainId::Post::Request::_rosDomainId) const& value) const;
  void setRosFrameId(decltype(api::rest::rosFrameId::Post::Request::_rosFrameId) const& value) const;
  void setRosNamespace(decltype(api::rest::rosNamespace::Post::Request::_rosNamespace) const& value) const;
  void setRosParentFrameId(decltype(api::rest::rosParentFrameId::Post::Request::_rosParentFrameId) const& value) const;
  void setRotationOffset(api::rest::RotationOffset::Post::Request const& request) const;
  void setScanDataConfig(api::rest::ScanDataConfig::Post::Request const& request) const;
  void setScanDataEnable(decltype(api::rest::ScanDataEnable::Post::Request::_ScanDataEnable) const& value) const;
  void setScanDataEthSettings(api::rest::ScanDataEthSettings::Post::Request const& request) const;
  void setScanDataFormat(decltype(api::rest::ScanDataFormat::Post::Request::_ScanDataFormat) const& value) const;
  void setScanMergeTrigger(decltype(api::rest::ScanMergeTrigger::Post::Request::_ScanMergeTrigger) const& value) const;
  void setScanMergerEnabled(decltype(api::rest::ScanMergerEnabled::Post::Request::_ScanMergerEnabled) const& value) const;
  void setScanMergerSource(decltype(api::rest::ScanMergerSource::Post::Request::_ScanMergerSource) const& value) const;
  void setSensitivityMode(decltype(api::rest::SensitivityMode::Post::Request::_SensitivityMode) const& value) const;
  void setSensorPosition(api::rest::SensorPosition::Post::Request const& request) const;
  void setTSCRole(decltype(api::rest::TSCRole::Post::Request::_TSCRole) const& value) const;
  void setTSCTCSrvAddr(decltype(api::rest::TSCTCSrvAddr::Post::Request::_TSCTCSrvAddr) const& value) const;
  void setTSCTCtimezone(decltype(api::rest::TSCTCtimezone::Post::Request::_TSCTCtimezone) const& value) const;
  void setTSCTCupdatetime(decltype(api::rest::TSCTCupdatetime::Post::Request::_TSCTCupdatetime) const& value) const;
  void setTemperatureAlarmConfiguration(api::rest::temperatureAlarmConfiguration::Post::Request const& request) const;
  void setTreatBlockedSectorsAsErrorSectors(decltype(api::rest::treatBlockedSectorsAsErrorSectors::Post::Request::_treatBlockedSectorsAsErrorSectors) const& value) const;
  void setWebserverEnabled(decltype(api::rest::SetWebserverEnabled::Post::Request::_Enable) const& value) const;
  void softReset(decltype(api::rest::SoftReset::Post::Request::_ProcessorNbr) const& value) const;
  void startScanMerge() const;
  void startTeachIn() const;
  void stopScanMerge() const;
  void stopTeachIn() const;
  auto writeEeprom() const -> decltype(api::rest::WriteEeprom::Post::Response::_Success);

protected:
  std::unique_ptr<SopasClient> m_sopasClient;
};

} // namespace sick::picoScan150::v2_3_3
