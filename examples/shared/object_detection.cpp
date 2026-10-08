/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// For a description of this example, refer to: examples/shared_learning_examples.md

#include "../examples_helper.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>

#if defined(USE_MULTISCAN100)
#  include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/GetFieldEvaluationContour.g.hpp>
#  include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_4/SetFieldEvaluationContour.g.hpp>
#  include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
using ConfiguratorT         = sick::multiScan100::v2_4_4::Configurator;
using SetContourRequest     = sick::multiScan100::v2_4_4::api::rest::SetFieldEvaluationContour::Post::Request;
using GetContourRequest     = sick::multiScan100::v2_4_4::api::rest::GetFieldEvaluationContour::Post::Response;
using FieldEvaluationResult = sick::multiScan100::v2_4_4::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult;
using EvaluationState = sick::multiScan100::v2_4_4::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem::State;
#elif defined(USE_LRS4000)
#  include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
#  include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/GetFieldEvaluationContour.g.hpp>
#  include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_10_0/SetFieldEvaluationContour.g.hpp>
using ConfiguratorT         = sick::LRS4000::v1_10_0::Configurator;
using SetContourRequest     = sick::LRS4000::v1_10_0::api::rest::SetFieldEvaluationContour::Post::Request;
using GetContourRequest     = sick::LRS4000::v1_10_0::api::rest::GetFieldEvaluationContour::Post::Response;
using FieldEvaluationResult = sick::LRS4000::v1_10_0::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult;
using EvaluationState = sick::LRS4000::v1_10_0::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem::State;
#else // Default to picoScan150
#  include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#  include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>
using ConfiguratorT         = sick::picoScan150::v2_3_3::Configurator;
using SetContourRequest     = sick::picoScan150::v2_3_3::api::rest::SetFieldEvaluationContour::Post::Request;
using GetContourRequest     = sick::picoScan150::v2_3_3::api::rest::GetFieldEvaluationContour::Post::Response;
using FieldEvaluationResult = sick::picoScan150::v2_3_3::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult;
using EvaluationState = sick::picoScan150::v2_3_3::api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult::EvaluationResultListItem::State;
#endif

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int GroupActivationStateInactive = 0;
constexpr int NumberOfEvaluationGroups     = 48;

void printFieldEvaluationContours(std::vector<GetContourRequest::Response::ContourItem> const& fieldContours)
{
  for (auto const& contour : fieldContours)
  {
    std::cout << "Points: \n";
    for (auto const& point : contour._Points)
    {
      std::cout << "- [" << point._x << ", " << point._y << "]\n";
    }
    std::cout << "Lower z limit: " << contour._LowerZLimit.value() << '\n';
    std::cout << "Upper z limit: " << contour._UpperZLimit.value() << '\n';
  }
}

void printEvaluationGroupStates(ConfiguratorT const& configurator)
{
  std::cout << "Getting group states from device.\n";
  auto const groupStates = configurator.getFieldEvaluationGroupState();
  for (size_t i = 0; i < groupStates.size(); ++i)
  {
    if (groupStates[i] != GroupActivationStateInactive) //only show active Fields
    {
      std::cout << "Group ID: " << i + 1 << ", State: " << groupStates[i] << '\n';
    }
  }
}

auto getAndPrintEvaluationFieldsStates(ConfiguratorT const& configurator) -> std::vector<std::uint16_t>
{
  std::cout << "Getting states of fields.\n";
  auto const result = configurator.getFieldEvaluationResult();
  std::cout << "Timestamp: " << result._Timestamp << '\n';
  std::vector<std::uint16_t> evaluationIDs;
  for (size_t i = 0; i < result._EvaluationResultList.size(); i++)
  {
    if (result._EvaluationResultList.at(i)._State != EvaluationState::NotConfigured)
    {
      std::cout << "ID: " << i + 1 << " State: " << static_cast<int>(result._EvaluationResultList.at(i)._State) << '\n';
      evaluationIDs.push_back(static_cast<std::uint16_t>(i + 1));
    }
  }
  return evaluationIDs;
}

void scaleEvaluationContours(std::vector<std::uint16_t> const& evaluationIDs, ConfiguratorT const& configurator)
{
  if (evaluationIDs.size() == 0)
  {
    std::cout << "No fields to change. Make sure that there is at least one field configured in the sensor.\n";
    return;
  }

  std::cout << "\nReading and changing field contours: \n\n";

  for (auto const& evaluationID : evaluationIDs)
  {
    auto const fieldContours = configurator.getFieldEvaluationContour(evaluationID);
    std::cout << "Contours for evaluation ID " << evaluationID << ":\n";
    printFieldEvaluationContours(fieldContours);

    // Change field contour points
    for (auto& contour : fieldContours)
    {
      std::cout << "Changing contour for evaluation ID " << evaluationID << ":\n";

      SetContourRequest request {evaluationID, {}, contour._LowerZLimit, contour._UpperZLimit};
      for (auto& point : contour._Points)
      {
        request._Points.push_back(SetContourRequest::PointsItem {point._x / 2, point._y / 2});
      }

      configurator.setFieldEvaluationContour(request);
    }
  }
}

/*
*  ! Expected Device Configuration: At least one field must already be stored in Object Detection. !
*/

int main(int argc, char* argv[])
{
  sick::examples::printSdkVersion();

  auto const sensorAddress = sick::examples::getSensorAddress("Object detection example", argc, argv);

  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>(sensorAddress.address, sensorAddress.restApiPort);

  // Change the default passwords during initial commissioning to secure your device.
  // Passwords can be updated via the web browser or API.
  // For production use, store passwords in a secure vault rather than in plain text.
  ConfiguratorT configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  try
  {
    printEvaluationGroupStates(configurator);
    auto const evaluationIDs = getAndPrintEvaluationFieldsStates(configurator);
    scaleEvaluationContours(evaluationIDs, configurator);
  }
  catch (std::exception const& exception)
  {
    std::cout << "Exception: " << exception.what() << '\n';
    return EXIT_FAILURE;
  }
}
