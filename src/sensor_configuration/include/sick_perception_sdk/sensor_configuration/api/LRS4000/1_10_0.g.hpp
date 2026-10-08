/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_10_0.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceIdent.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LocationName.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SerialNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FirmwareVersion.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetPassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/getChallenge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/changePassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FindMe.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OrderNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/WriteEeprom.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SCdevicestate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SoftReset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/RebootDevice.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LoadFactoryDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LoadApplicationDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LastParaDate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LastParaTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DoDiagnosisDump.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/GetDiagnosisDumpInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/httpsStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/certificateBundleInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPGateAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPMask.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherAuxEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherAddressingMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherDHCPFallback.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EthernetUpdate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPGateAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherIPMaskDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DataOutputRange.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/InputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OutputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PortState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mResetOutputCounter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FREchoFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ParticleFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherMACAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableColaScan.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EtherColaTransmitTimeout.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanDataScaleFactor.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SensitivityMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetScanConfigList.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncSetting.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncResolution.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ActualEncSpeed.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LEDEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PowerOnCnt.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DailyOpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/OpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/CurrentTempDev.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DeviceType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationData.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationActiveSectors.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ContaminationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableInertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/InertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SyncMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SyncPhase.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/MotorSyncStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanDataFormat.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/PortConfiguration.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetOutput.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mStartMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mStandby.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/MeanFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LFPmedianfilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/LFPradialDistanceRangeFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetWebserverEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ActivateEvaluationGroup.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/GetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EvaluationGroupType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationGroupState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/FieldEvaluationApplicationState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EnableDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EvaluationsToLog.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ResetDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StartTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StopTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/perpendicularDistanceResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergerEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergerSource.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/ScanMergeTrigger.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/RotationOffset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderTransformationType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderRotation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/EncoderTranslation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StartScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/StopScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCRole.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCSrvAddr.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCtimezone.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/TSCTCupdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/DateTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/mSetDateTime.g.hpp>

