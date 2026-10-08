/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_9_1.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceIdent.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LocationName.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SerialNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FirmwareVersion.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetPassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/getChallenge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/changePassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FindMe.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OrderNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/WriteEeprom.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SCdevicestate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SoftReset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/RebootDevice.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LoadFactoryDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LoadApplicationDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LastParaDate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LastParaTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DoDiagnosisDump.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/GetDiagnosisDumpInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPGateAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPMask.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherAuxEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherAddressingMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherDHCPFallback.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EthernetUpdate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPGateAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherIPMaskDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DataOutputRange.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/InputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OutputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PortState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mResetOutputCounter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FREchoFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ParticleFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherMACAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableColaScan.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EtherColaTransmitTimeout.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanDataScaleFactor.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SensitivityMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetScanConfigList.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncSetting.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncResolution.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ActualEncSpeed.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LEDEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PowerOnCnt.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DailyOpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/OpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/CurrentTempDev.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DeviceType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationData.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationActiveSectors.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ContaminationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableInertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/InertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SyncMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SyncPhase.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/MotorSyncStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanDataFormat.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/PortConfiguration.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetOutput.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mStartMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mStandby.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/MeanFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LFPmedianfilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/LFPradialDistanceRangeFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetWebserverEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ActivateEvaluationGroup.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/SetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/GetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationGroupState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/FieldEvaluationApplicationState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EnableDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EvaluationsToLog.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ResetDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StartTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StopTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergerEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergerSource.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/ScanMergeTrigger.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/RotationOffset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderTransformationType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderRotation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/EncoderTranslation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StartScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/StopScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCRole.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCSrvAddr.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCtimezone.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/TSCTCupdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/DateTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1/mSetDateTime.g.hpp>

