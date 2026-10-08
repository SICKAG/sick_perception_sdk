/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "ParameterBackupRestore.hpp"
#include "HttpHelpers.hpp"
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SopasClient.hpp>

#include <string>

namespace sick::parameters {

namespace backup {

auto fetchFromSensor(SopasClient const& sopasClient) -> std::string
{
  auto const sessionToken = sopasClient.createSessionToken();

  HttpRequest request;
  request.method      = HttpMethod::Get;
  request.path        = "/api/parameterbackup";
  request.headers     = sessionHeaders(sessionToken);
  auto const response = sopasClient.httpClient().send(request);
  throwIfNotOk(response, "Download of parameter backup");
  return response.body;
}

} // namespace backup

namespace restore {

void uploadToSensor(std::string const& backupContent, SopasClient const& sopasClient)
{
  HttpRequest request;
  request.method          = HttpMethod::Put;
  request.path            = "/api/parameterbackup";
  request.contentType     = "application/octet-stream";
  request.body            = backupContent;
  auto const sessionToken = sopasClient.createSessionToken();
  request.headers         = sessionHeaders(sessionToken);
  auto const response     = sopasClient.httpClient().send(request);
  throwIfNotOk(response, "Upload of parameter backup");
}

} // namespace restore

} // namespace sick::parameters
