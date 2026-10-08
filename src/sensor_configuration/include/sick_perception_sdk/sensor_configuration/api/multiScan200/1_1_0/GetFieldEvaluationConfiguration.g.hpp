/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetFieldEvaluationConfiguration.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <string>
#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /GetFieldEvaluationConfiguration.
*/
struct GetFieldEvaluationConfiguration
{

  constexpr static const char* methodName = "GetFieldEvaluationConfiguration";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns the configuration of an existing field.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(int EvaluationId)
        : _EvaluationId(EvaluationId)
      {}

      int _EvaluationId;
    };

    struct Response
    {
      struct ConfigurationItem
      {
        struct Configuration
        {
          enum class Source
          {
            Standard = 0,
            Highres6 = 1,
            Highres14 = 2,
          };

          struct EvaluationParamsMaskBasedItem
          {
            EvaluationParamsMaskBasedItem() = default;

            explicit EvaluationParamsMaskBasedItem(NumericRange<int, 1, 100, 80> InfringementThresholdFactor)
              : _InfringementThresholdFactor(InfringementThresholdFactor)
            {}

            NumericRange<int, 1, 100, 80> _InfringementThresholdFactor;
          };

          struct EvaluationParamsSegmentationBasedItem
          {
            EvaluationParamsSegmentationBasedItem() = default;

            explicit EvaluationParamsSegmentationBasedItem(int SampleParam1)
              : _SampleParam1(SampleParam1)
            {}

            int _SampleParam1;
          };

          struct EvaluationParamsCommonItem
          {
            EvaluationParamsCommonItem() = default;

            explicit EvaluationParamsCommonItem(NumericRange<int, 0, 5000, 200> MinimumObjectSizeHorizontal, NumericRange<int, 0, 5000, 200> MinimumObjectSizeVertical, bool OcclusionHandling, bool TreatMissingDataAsInfringed, NumericRange<int, 1, 10000, 300> TimeForInfringedState, NumericRange<int, 1, 10000, 50> TimeForFreeState, int Reserved3, int Reserved4)
              : _MinimumObjectSizeHorizontal(MinimumObjectSizeHorizontal), _MinimumObjectSizeVertical(MinimumObjectSizeVertical), _OcclusionHandling(OcclusionHandling), _TreatMissingDataAsInfringed(TreatMissingDataAsInfringed), _TimeForInfringedState(TimeForInfringedState), _TimeForFreeState(TimeForFreeState), _Reserved3(Reserved3), _Reserved4(Reserved4)
            {}

            NumericRange<int, 0, 5000, 200> _MinimumObjectSizeHorizontal;
            NumericRange<int, 0, 5000, 200> _MinimumObjectSizeVertical;
            bool _OcclusionHandling;
            bool _TreatMissingDataAsInfringed;
            NumericRange<int, 1, 10000, 300> _TimeForInfringedState;
            NumericRange<int, 1, 10000, 50> _TimeForFreeState;
            int _Reserved3;
            int _Reserved4;
          };

          struct EvaluationParamsExitSizeItem
          {
            EvaluationParamsExitSizeItem() = default;

            explicit EvaluationParamsExitSizeItem(bool disableExitSize, NumericRange<int, 0, 100, 70> exitSizeVertical, NumericRange<int, 0, 100, 100> exitSizeHorizontal)
              : _disableExitSize(disableExitSize), _exitSizeVertical(exitSizeVertical), _exitSizeHorizontal(exitSizeHorizontal)
            {}

            bool _disableExitSize;
            NumericRange<int, 0, 100, 70> _exitSizeVertical;
            NumericRange<int, 0, 100, 100> _exitSizeHorizontal;
          };

          Configuration() = default;

          explicit Configuration(int Version, Source Source, std::string Name, int ID, std::vector<EvaluationParamsMaskBasedItem> EvaluationParamsMaskBased, std::vector<EvaluationParamsSegmentationBasedItem> EvaluationParamsSegmentationBased, std::vector<EvaluationParamsCommonItem> EvaluationParamsCommon, std::vector<EvaluationParamsExitSizeItem> EvaluationParamsExitSize, std::vector<int> VolumeList)
            : _Version(Version), _Source(Source), _Name(std::move(Name)), _ID(ID), _EvaluationParamsMaskBased(EvaluationParamsMaskBased), _EvaluationParamsSegmentationBased(EvaluationParamsSegmentationBased), _EvaluationParamsCommon(EvaluationParamsCommon), _EvaluationParamsExitSize(EvaluationParamsExitSize), _VolumeList(VolumeList)
          {}

          int _Version;
          Source _Source;
          std::string _Name;
          int _ID;
          std::vector<EvaluationParamsMaskBasedItem> _EvaluationParamsMaskBased;
          std::vector<EvaluationParamsSegmentationBasedItem> _EvaluationParamsSegmentationBased;
          std::vector<EvaluationParamsCommonItem> _EvaluationParamsCommon;
          std::vector<EvaluationParamsExitSizeItem> _EvaluationParamsExitSize;
          std::vector<int> _VolumeList;
        };

        ConfigurationItem() = default;

        explicit ConfigurationItem(int EvaluationId, std::string Name, Configuration Configuration)
          : _EvaluationId(EvaluationId), _Name(std::move(Name)), _Configuration(Configuration)
        {}

        int _EvaluationId;
        std::string _Name;
        Configuration _Configuration;
      };

      Response() = default;

      explicit Response(std::vector<ConfigurationItem> Configuration)
        : _Configuration(Configuration)
      {}

      std::vector<ConfigurationItem> _Configuration;
    };

  }; // struct Post

}; // struct GetFieldEvaluationConfiguration

} // namespace sick::multiScan200::v1_1_0::api::rest
