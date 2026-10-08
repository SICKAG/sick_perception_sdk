/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_9_1.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceIdent.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LocationName.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SerialNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FirmwareVersion.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetPassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/getChallenge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/changePassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FindMe.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OrderNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/WriteEeprom.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SCdevicestate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SoftReset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/RebootDevice.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LoadFactoryDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LoadApplicationDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LastParaDate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LastParaTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DoDiagnosisDump.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/GetDiagnosisDumpInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPGateAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPMask.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherAuxEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherAddressingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherDHCPFallback.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EthernetUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPGateAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPMaskDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DataOutputRange.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/InputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OutputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PortState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mResetOutputCounter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FREchoFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ParticleFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherMACAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableColaScan.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherColaTransmitTimeout.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanDataScaleFactor.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SensitivityMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetScanConfigList.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncSetting.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncResolution.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ActualEncSpeed.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LEDEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PowerOnCnt.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DailyOpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/CurrentTempDev.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationData.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationActiveSectors.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableInertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/InertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SyncMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SyncPhase.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/MotorSyncStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanDataFormat.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PortConfiguration.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetOutput.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mStandby.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/MeanFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LFPmedianfilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LFPradialDistanceRangeFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetWebserverEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ActivateEvaluationGroup.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/GetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationGroupState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationApplicationState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EvaluationsToLog.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ResetDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StartTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StopTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergerEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergerSource.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergeTrigger.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/RotationOffset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderTransformationType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderRotation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderTranslation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StartScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StopScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCRole.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCSrvAddr.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCtimezone.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCupdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DateTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mSetDateTime.nlohmann_json.g.hpp>

