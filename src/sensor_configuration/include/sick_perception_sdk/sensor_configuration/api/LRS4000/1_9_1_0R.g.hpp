/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file 1_9_1_0R.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceIdent.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LocationName.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SerialNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FirmwareVersion.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetPassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/getChallenge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/changePassword.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FindMe.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OrderNumber.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/WriteEeprom.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SCdevicestate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SoftReset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/RebootDevice.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LoadFactoryDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LoadApplicationDefaults.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LastParaDate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LastParaTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DoDiagnosisDump.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/GetDiagnosisDumpInfo.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPGateAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPMask.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherAuxEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherAddressingMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherDHCPFallback.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EthernetUpdate.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPGateAddressDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherIPMaskDHCP.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DataOutputRange.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/InputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OutputState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PortState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mResetOutputCounter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FREchoFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ParticleFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherMACAddress.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableColaScan.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherCoLaAEventsEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EtherColaTransmitTimeout.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanDataScaleFactor.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SensitivityMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetScanConfigList.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncSetting.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncResolution.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ActualEncSpeed.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LEDEnable.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PowerOnCnt.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DailyOpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/OpHours.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/CurrentTempDev.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationConfig.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationData.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationActiveSectors.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ContaminationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableInertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/InertialMeasurementUnit.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SyncMode.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SyncPhase.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/MotorSyncStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanDataFormat.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/PortConfiguration.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetOutput.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mStartMeasure.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mStandby.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/MeanFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPmedianfilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/LFPradialDistanceRangeFilter.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetWebserverEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ActivateEvaluationGroup.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/SetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/GetFieldEvaluationContour.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationGroupState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationApplicationState.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EnableDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ResetDetectionHistory.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StartTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StopTeachIn.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergerEnabled.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergerSource.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/ScanMergeTrigger.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/RotationOffset.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderTransformationType.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderRotation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/EncoderTranslation.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StartScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/StopScanMerge.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCRole.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCSrvAddr.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCtimezone.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCupdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DateTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mSetDateTime.g.hpp>

