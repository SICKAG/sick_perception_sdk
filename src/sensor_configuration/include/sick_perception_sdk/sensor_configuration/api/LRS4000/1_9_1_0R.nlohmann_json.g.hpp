/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_9_1_0R.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceIdent.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LocationName.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SerialNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FirmwareVersion.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetPassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/getChallenge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/changePassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FindMe.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OrderNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/WriteEeprom.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SCdevicestate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SoftReset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/RebootDevice.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LoadFactoryDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LoadApplicationDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LastParaDate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LastParaTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DoDiagnosisDump.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/GetDiagnosisDumpInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPGateAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPMask.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherAuxEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherAddressingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherDHCPFallback.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EthernetUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPGateAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPMaskDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DataOutputRange.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/InputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OutputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PortState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mResetOutputCounter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FREchoFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ParticleFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherMACAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableColaScan.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherCoLaAEventsEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherColaTransmitTimeout.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanDataScaleFactor.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SensitivityMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetScanConfigList.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncSetting.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncResolution.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ActualEncSpeed.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LEDEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PowerOnCnt.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DailyOpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/CurrentTempDev.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationData.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationActiveSectors.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableInertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/InertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SyncMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SyncPhase.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/MotorSyncStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanDataFormat.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PortConfiguration.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetOutput.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mStandby.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/MeanFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPmedianfilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPradialDistanceRangeFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetWebserverEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ActivateEvaluationGroup.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/GetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationGroupState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationApplicationState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ResetDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StartTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StopTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergerEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergerSource.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergeTrigger.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/RotationOffset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderTransformationType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderRotation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderTranslation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StartScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StopScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCRole.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCSrvAddr.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCtimezone.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCupdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DateTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mSetDateTime.nlohmann_json.g.hpp>

