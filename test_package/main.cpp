/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/version.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>

#include <sick_perception_sdk/sensor_configuration/api/LRS4000/LRS4000.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/LRS4000.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/multiScan100.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/multiScan100.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan120.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/picoScan100/picoScan150.nlohmann_json.g.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  std::cout << "SICK Perception SDK Version: " << sick::version() << std::endl;

  // Test compilation of library compact_format
  sick::compact::scan_data::Parser parser;

  // Test compilation of library drivers
  sick::picoScan100::Driver driver;

  // Test compilation of library sensor_configuration
  auto const httpClient = std::make_shared<sick::httplib_client::HttpClient>("127.0.0.1", 80);
  sick::picoScan150::v2_2_1_0R::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  return 0;
}
