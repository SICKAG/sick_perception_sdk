/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file Endpoints.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan200/1_1_0.g.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>

#include <memory>
#include <string>

namespace sick {
class SopasClient;
} // namespace sick

namespace sick::multiScan200::v1_1_0 {

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
  auto getAmbientPixelCountVertical() const -> decltype(api::rest::ambientPixelCountVertical::Get::Response::_ambientPixelCountVertical);
  auto getAngleRangeFocusFilter() const -> api::rest::angleRangeFocusFilter::Get::Response;
  auto getAutoStartMeasure() const -> decltype(api::rest::AutoStartMeasure::Get::Response::_AutoStartMeasure);
  auto getBloomingFilter() const -> api::rest::bloomingFilter::Get::Response;
  auto getCertificateBundleInfo() const -> api::rest::certificateBundleInfo::Get::Response;
  void getChallenge(decltype(api::rest::getChallenge::Post::Request::_user) const& value) const;
  auto getCompactTelegramType6Content() const -> api::rest::compactTelegramType6Content::Get::Response;
  auto getContaminationActiveSectors() const -> decltype(api::rest::ContaminationActiveSectors::Get::Response::_ContaminationActiveSectors);
  auto getContaminationConfig() const -> api::rest::ContaminationConfig::Get::Response;
  auto getContaminationData() const -> decltype(api::rest::ContaminationData::Get::Response::_ContaminationData);
  auto getContaminationResult() const -> api::rest::ContaminationResult::Get::Response;
  auto getCreateParameterBackupResult() const -> api::rest::CreateParameterBackupResult::Get::Response;
  auto getCurrentTempDev() const -> decltype(api::rest::CurrentTempDev::Get::Response::_CurrentTempDev);
  auto getDailyOpHours() const -> decltype(api::rest::DailyOpHours::Get::Response::_DailyOpHours);
  auto getDataOutputMode() const -> decltype(api::rest::dataOutputMode::Get::Response::_dataOutputMode);
  auto getDeviceIdent() const -> api::rest::DeviceIdent::Get::Response;
  auto getDeviceStatus() const -> decltype(api::rest::DeviceStatus::Get::Response::_DeviceStatus);
  auto getDeviceType() const -> decltype(api::rest::DeviceType::Get::Response::_DeviceType);
  auto getDiagnosisDumpInfo() const -> api::rest::GetDiagnosisDumpInfo::Post::Response;
  auto getEnableHighPrecisionMode() const -> decltype(api::rest::enableHighPrecisionMode::Get::Response::_enableHighPrecisionMode);
  auto getEtherAddressingMode() const -> decltype(api::rest::EtherAddressingMode::Get::Response::_EtherAddressingMode);
  auto getEtherAuxEnabled() const -> decltype(api::rest::EtherAuxEnabled::Get::Response::_EtherAuxEnabled);
  auto getEtherCoLaScanMode() const -> decltype(api::rest::EtherCoLaScanMode::Get::Response::_EtherCoLaScanMode);
  auto getEtherDHCPFallback() const -> decltype(api::rest::EtherDHCPFallback::Get::Response::_EtherDHCPFallback);
  auto getEtherIPAddress() const -> decltype(api::rest::EtherIPAddress::Get::Response::_EtherIPAddress);
  auto getEtherIPAddressDHCP() const -> decltype(api::rest::EtherIPAddressDHCP::Get::Response::_EtherIPAddressDHCP);
  auto getEtherIPGateAddress() const -> decltype(api::rest::EtherIPGateAddress::Get::Response::_EtherIPGateAddress);
  auto getEtherIPGateAddressDHCP() const -> decltype(api::rest::EtherIPGateAddressDHCP::Get::Response::_EtherIPGateAddressDHCP);
  auto getEtherIPMask() const -> decltype(api::rest::EtherIPMask::Get::Response::_EtherIPMask);
  auto getEtherIPMaskDHCP() const -> decltype(api::rest::EtherIPMaskDHCP::Get::Response::_EtherIPMaskDHCP);
  auto getEtherMACAddress() const -> decltype(api::rest::EtherMACAddress::Get::Response::_EtherMACAddress);
  auto getEvaluationConfigState() const -> api::rest::EvaluationConfigState::Get::Response;
  auto getFREchoFilter() const -> decltype(api::rest::FREchoFilter::Get::Response::_FREchoFilter);
  auto getFieldEvaluationApplicationState() const -> decltype(api::rest::FieldEvaluationApplicationState::Get::Response::_FieldEvaluationApplicationState);
  auto getFieldEvaluationConfiguration(decltype(api::rest::GetFieldEvaluationConfiguration::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationConfiguration::Post::Response::_Configuration);
  auto getFieldEvaluationContour(decltype(api::rest::GetFieldEvaluationContour::Post::Request::_EvaluationId) const& value) const -> decltype(api::rest::GetFieldEvaluationContour::Post::Response::_Contour);
  auto getFieldEvaluationGroupState() const -> decltype(api::rest::FieldEvaluationGroupState::Get::Response::_FieldEvaluationGroupState);
  auto getFieldEvaluationResult() const -> decltype(api::rest::FieldEvaluationResult::Get::Response::_FieldEvaluationResult);
  auto getFirmwareVersion() const -> decltype(api::rest::FirmwareVersion::Get::Response::_FirmwareVersion);
  auto getHorizontalFieldOfViewCenterAngle() const -> decltype(api::rest::horizontalFieldOfViewCenterAngle::Get::Response::_horizontalFieldOfViewCenterAngle);
  auto getHttpsStatus() const -> api::rest::httpsStatus::Get::Response;
  auto getInertialMeasurementUnit() const -> api::rest::InertialMeasurementUnit::Get::Response;
  auto getInputState() const -> api::rest::InputState::Get::Response;
  auto getLEDEnable() const -> decltype(api::rest::LEDEnable::Get::Response::_LEDEnable);
  auto getLEDState() const -> decltype(api::rest::LEDState::Get::Response::_LEDState);
  auto getLFPintervalFilter() const -> api::rest::LFPintervalFilter::Get::Response;
  auto getLFTchecksum() const -> api::rest::LFTchecksum::Get::Response;
  auto getLSPdatetime() const -> decltype(api::rest::LSPdatetime::Get::Response::_LSPdatetime);
  auto getLastParaDate() const -> decltype(api::rest::LastParaDate::Get::Response::_LastParaDate);
  auto getLastParaTime() const -> decltype(api::rest::LastParaTime::Get::Response::_LastParaTime);
  auto getLocationName() const -> decltype(api::rest::LocationName::Get::Response::_LocationName);
  auto getOpHours() const -> decltype(api::rest::OpHours::Get::Response::_OpHours);
  auto getOrderNumber() const -> decltype(api::rest::OrderNumber::Get::Response::_OrderNumber);
  auto getOutputState() const -> api::rest::OutputState::Get::Response;
  auto getParticleFilter() const -> api::rest::particleFilter::Get::Response;
  auto getPerformanceProfileNumber() const -> decltype(api::rest::PerformanceProfileNumber::Get::Response::_PerformanceProfileNumber);
  auto getPortConfiguration() const -> decltype(api::rest::PortConfiguration::Get::Response::_PortConfiguration);
  auto getPortState() const -> api::rest::PortState::Get::Response;
  auto getPowerOnCnt() const -> decltype(api::rest::PowerOnCnt::Get::Response::_PowerOnCnt);
  auto getRestoreParameterBackupResult() const -> api::rest::RestoreParameterBackupResult::Get::Response;
  auto getRosDomainId() const -> decltype(api::rest::rosDomainId::Get::Response::_rosDomainId);
  auto getRosFrameId() const -> decltype(api::rest::rosFrameId::Get::Response::_rosFrameId);
  auto getRosNamespace() const -> decltype(api::rest::rosNamespace::Get::Response::_rosNamespace);
  auto getRosParentFrameId() const -> decltype(api::rest::rosParentFrameId::Get::Response::_rosParentFrameId);
  auto getRosPointCloud2Content() const -> api::rest::rosPointCloud2Content::Get::Response;
  auto getSCdevicestate() const -> decltype(api::rest::SCdevicestate::Get::Response::_SCdevicestate);
  auto getScanConfig() const -> api::rest::ScanConfig::Get::Response;
  auto getSensitivityMode() const -> decltype(api::rest::SensitivityMode::Get::Response::_SensitivityMode);
  auto getSensorPosition() const -> api::rest::SensorPosition::Get::Response;
  auto getSerialNumber() const -> decltype(api::rest::SerialNumber::Get::Response::_SerialNumber);
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
  auto mResetOutputCounter() const -> decltype(api::rest::mResetOutputCounter::Post::Response::_ErrorCode);
  auto mStandby() const -> decltype(api::rest::mStandby::Post::Response::_ErrorCode);
  auto mStartMeasure() const -> decltype(api::rest::mStartMeasure::Post::Response::_ErrorCode);
  auto mStopMeasure() const -> decltype(api::rest::mStopMeasure::Post::Response::_ErrorCode);
  void rebootDevice() const;
  auto removeCertificateBundle() const -> api::rest::removeCertificateBundle::Post::Response;
  auto restoreParameterBackup(api::rest::RestoreParameterBackup::Post::Request const& request) const -> decltype(api::rest::RestoreParameterBackup::Post::Response::_Result);
  void runFirmwareUpdate() const;
  void setAmbientPixelCountVertical(decltype(api::rest::ambientPixelCountVertical::Post::Request::_ambientPixelCountVertical) const& value) const;
  void setAngleRangeFocusFilter(api::rest::angleRangeFocusFilter::Post::Request const& request) const;
  void setAutoStartMeasure(decltype(api::rest::AutoStartMeasure::Post::Request::_AutoStartMeasure) const& value) const;
  void setBloomingFilter(api::rest::bloomingFilter::Post::Request const& request) const;
  auto setCertificateBundle(api::rest::setCertificateBundle::Post::Request const& request) const -> api::rest::setCertificateBundle::Post::Response;
  void setCompactTelegramType6Content(api::rest::compactTelegramType6Content::Post::Request const& request) const;
  void setContaminationConfig(api::rest::ContaminationConfig::Post::Request const& request) const;
  void setDataOutputMode(decltype(api::rest::dataOutputMode::Post::Request::_dataOutputMode) const& value) const;
  auto setDateTimeUTC(decltype(api::rest::setDateTimeUTC::Post::Request::_DateTime) const& value) const -> decltype(api::rest::setDateTimeUTC::Post::Response::_ErrorCode);
  void setEnableHighPrecisionMode(decltype(api::rest::enableHighPrecisionMode::Post::Request::_enableHighPrecisionMode) const& value) const;
  void setEtherAddressingMode(decltype(api::rest::EtherAddressingMode::Post::Request::_EtherAddressingMode) const& value) const;
  void setEtherAuxEnabled(decltype(api::rest::EtherAuxEnabled::Post::Request::_EtherAuxEnabled) const& value) const;
  void setEtherCoLaScanMode(decltype(api::rest::EtherCoLaScanMode::Post::Request::_EtherCoLaScanMode) const& value) const;
  void setEtherDHCPFallback(decltype(api::rest::EtherDHCPFallback::Post::Request::_EtherDHCPFallback) const& value) const;
  void setEtherIPAddress(decltype(api::rest::EtherIPAddress::Post::Request::_EtherIPAddress) const& value) const;
  void setEtherIPGateAddress(decltype(api::rest::EtherIPGateAddress::Post::Request::_EtherIPGateAddress) const& value) const;
  void setEtherIPMask(decltype(api::rest::EtherIPMask::Post::Request::_EtherIPMask) const& value) const;
  void setFREchoFilter(decltype(api::rest::FREchoFilter::Post::Request::_FREchoFilter) const& value) const;
  auto setFieldEvaluationConfiguration(api::rest::SetFieldEvaluationConfiguration::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationConfiguration::Post::Response::_ErrorCode);
  auto setFieldEvaluationContour(api::rest::SetFieldEvaluationContour::Post::Request const& request) const -> decltype(api::rest::SetFieldEvaluationContour::Post::Response::_ErrorCode);
  void setHorizontalFieldOfViewCenterAngle(decltype(api::rest::horizontalFieldOfViewCenterAngle::Post::Request::_horizontalFieldOfViewCenterAngle) const& value) const;
  void setLEDEnable(decltype(api::rest::LEDEnable::Post::Request::_LEDEnable) const& value) const;
  void setLFPintervalFilter(api::rest::LFPintervalFilter::Post::Request const& request) const;
  void setLocationName(decltype(api::rest::LocationName::Post::Request::_LocationName) const& value) const;
  auto setOutput(api::rest::SetOutput::Post::Request const& request) const -> decltype(api::rest::SetOutput::Post::Response::_Success);
  void setParticleFilter(api::rest::particleFilter::Post::Request const& request) const;
  auto setPassword(api::rest::SetPassword::Post::Request const& request) const -> decltype(api::rest::SetPassword::Post::Response::_bSuccess);
  void setPortConfiguration(decltype(api::rest::PortConfiguration::Post::Request::_PortConfiguration) const& value) const;
  void setRosDomainId(decltype(api::rest::rosDomainId::Post::Request::_rosDomainId) const& value) const;
  void setRosFrameId(decltype(api::rest::rosFrameId::Post::Request::_rosFrameId) const& value) const;
  void setRosNamespace(decltype(api::rest::rosNamespace::Post::Request::_rosNamespace) const& value) const;
  void setRosParentFrameId(decltype(api::rest::rosParentFrameId::Post::Request::_rosParentFrameId) const& value) const;
  void setRosPointCloud2Content(api::rest::rosPointCloud2Content::Post::Request const& request) const;
  auto setScanConfigList(decltype(api::rest::SetScanConfigList::Post::Request::_ScanConfigList) const& value) const -> decltype(api::rest::SetScanConfigList::Post::Response::_eScanConfigError);
  void setSensitivityMode(decltype(api::rest::SensitivityMode::Post::Request::_SensitivityMode) const& value) const;
  void setSensorPosition(api::rest::SensorPosition::Post::Request const& request) const;
  void setTSCRole(decltype(api::rest::TSCRole::Post::Request::_TSCRole) const& value) const;
  void setTSCTCSrvAddr(decltype(api::rest::TSCTCSrvAddr::Post::Request::_TSCTCSrvAddr) const& value) const;
  void setTSCTCtimezone(decltype(api::rest::TSCTCtimezone::Post::Request::_TSCTCtimezone) const& value) const;
  void setTSCTCupdatetime(decltype(api::rest::TSCTCupdatetime::Post::Request::_TSCTCupdatetime) const& value) const;
  void setTreatBlockedSectorsAsErrorSectors(decltype(api::rest::treatBlockedSectorsAsErrorSectors::Post::Request::_treatBlockedSectorsAsErrorSectors) const& value) const;
  void setWebserverEnabled(decltype(api::rest::SetWebserverEnabled::Post::Request::_Enable) const& value) const;
  void softReset(decltype(api::rest::SoftReset::Post::Request::_ProcessorNbr) const& value) const;
  auto writeEeprom() const -> decltype(api::rest::WriteEeprom::Post::Response::_Success);

protected:
  std::unique_ptr<SopasClient> m_sopasClient;
};

} // namespace sick::multiScan200::v1_1_0
