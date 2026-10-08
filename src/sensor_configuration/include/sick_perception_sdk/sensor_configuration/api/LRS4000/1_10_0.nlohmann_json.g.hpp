/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_10_0.nlohmann_json.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceIdent.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LocationName.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SerialNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FirmwareVersion.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetPassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/getChallenge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/changePassword.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FindMe.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OrderNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/WriteEeprom.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SCdevicestate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SoftReset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/RebootDevice.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LoadFactoryDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LoadApplicationDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LastParaDate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LastParaTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DoDiagnosisDump.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/GetDiagnosisDumpInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/httpsStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/certificateBundleInfo.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPGateAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPMask.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherAuxEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherAddressingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherDHCPFallback.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EthernetUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPGateAddressDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPMaskDHCP.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DataOutputRange.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/InputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OutputState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PortState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mResetOutputCounter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FREchoFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ParticleFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherMACAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableColaScan.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherColaTransmitTimeout.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanDataScaleFactor.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SensitivityMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetScanConfigList.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncSetting.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncResolution.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ActualEncSpeed.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LEDEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PowerOnCnt.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DailyOpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OpHours.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/CurrentTempDev.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationData.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationActiveSectors.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableInertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/InertialMeasurementUnit.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SyncMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SyncPhase.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/MotorSyncStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanDataFormat.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PortConfiguration.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetOutput.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mStandby.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/MeanFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LFPmedianfilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LFPradialDistanceRangeFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetWebserverEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ActivateEvaluationGroup.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/GetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EvaluationGroupType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationGroupState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationApplicationState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EvaluationsToLog.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ResetDetectionHistory.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StartTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StopTeachIn.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/perpendicularDistanceResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergerEnabled.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergerSource.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergeTrigger.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/RotationOffset.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderTransformationType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderRotation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderTranslation.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StartScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StopScanMerge.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCRole.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCSrvAddr.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCtimezone.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCupdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DateTime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mSetDateTime.nlohmann_json.g.hpp>

