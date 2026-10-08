/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 2_2_1.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/checkCredentials.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceIdent.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LocationName.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SerialNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/FirmwareVersion.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetPassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/getChallenge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/changePassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EnableUserLevel.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OrderNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/WriteEeprom.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SCdevicestate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SoftReset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RebootDevice.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LoadFactoryDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LoadApplicationDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LastParaDate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LastParaTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DoDiagnosisDump.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/GetDiagnosisDumpInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OutputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PortState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mResetOutputCounter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPGateAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPMask.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherAuxEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherCoLaScanMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherAddressingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherDHCPFallback.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EthernetUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPGateAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPMaskDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/httpsStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/certificateBundleInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/removeCertificateBundle.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/setCertificateBundle.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetWebserverEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/GetWebserverEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EnableLegacyUserLevel.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherMACAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PowerOnCnt.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DailyOpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RunFirmwareUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/UpdateState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/CreateParameterBackup.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RestoreParameterBackup.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataEthSettings.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataFormat.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosFrameId.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosParentFrameId.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosNamespace.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PortConfiguration.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetOutput.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LEDState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LEDEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/FindMe.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LFTchecksum.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStandby.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStopMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/AutoStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/temperatureAlarmConfiguration.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/temperatureAlarmStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/CurrentTempDev.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/operatingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LFPparticle.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SensorPosition.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCRole.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCSrvAddr.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCtimezone.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCupdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LSPdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LSPsetdatetime.nlohmann_json.g.hpp>

