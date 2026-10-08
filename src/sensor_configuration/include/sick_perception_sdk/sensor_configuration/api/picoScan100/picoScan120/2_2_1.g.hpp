/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 2_2_1.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/checkCredentials.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceIdent.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LocationName.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SerialNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/FirmwareVersion.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetPassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/getChallenge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/changePassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EnableUserLevel.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OrderNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/WriteEeprom.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SCdevicestate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SoftReset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RebootDevice.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LoadFactoryDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LoadApplicationDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LastParaDate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LastParaTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DoDiagnosisDump.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/GetDiagnosisDumpInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OutputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PortState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mResetOutputCounter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPGateAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPMask.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherAuxEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherCoLaScanMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherAddressingMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherDHCPFallback.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EthernetUpdate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPGateAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherIPMaskDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/httpsStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/certificateBundleInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/removeCertificateBundle.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/setCertificateBundle.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetWebserverEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/GetWebserverEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EnableLegacyUserLevel.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/EtherMACAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PowerOnCnt.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DailyOpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/OpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/DeviceType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RunFirmwareUpdate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/UpdateState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/CreateParameterBackup.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/RestoreParameterBackup.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataEthSettings.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanDataFormat.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosFrameId.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosParentFrameId.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/rosNamespace.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/PortConfiguration.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SetOutput.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LEDState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LEDEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/FindMe.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LFTchecksum.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStartMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStandby.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/mStopMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/AutoStartMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/ScanConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/temperatureAlarmConfiguration.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/temperatureAlarmStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/CurrentTempDev.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/operatingMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LFPparticle.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/SensorPosition.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCRole.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCSrvAddr.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCtimezone.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/TSCTCupdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LSPdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120/2_2_1/LSPsetdatetime.g.hpp>

