/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/version.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>
#include <sick_perception_sdk/drivers/multiScan100/MultiScan100Driver.hpp>
#include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>
#include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/httplib_client/HttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/LRS4000/LRS4000Configurator.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>
#include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>
#include <sick_perception_sdk/sensor_configuration/multiScan200/MultiScan200Configurator.hpp>
#include <sick_perception_sdk/sensor_configuration/picoScan150/PicoScan150Configurator.hpp>

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
  sick::picoScan150::v2_3_3::Configurator configurator(httpClient, sick::UserLevel::Service, "servicelevel");

  return 0;
}
