/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/sensor_configuration/multiScan100/MultiScan100Configurator.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Temperature.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SensorConfigurator.hpp>
#include <sick_perception_sdk/sensor_configuration/api/FieldEvaluationContour.hpp>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>
#include <sick_perception_sdk/sensor_configuration/api/SensorPosition.hpp>
#include <sick_perception_sdk/sensor_configuration/api/SrtRest.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ContaminationConfig.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ContaminationData.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ContaminationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/CurrentTempDev.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/DeviceStatus.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/DeviceType.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherAddressingMode.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherIPAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherIPGateAddress.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EtherIPMask.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/EthernetUpdate.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FREchoFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FieldEvaluationGroupState.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FieldEvaluationResult.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FindMe.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FirmwareVersion.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/GetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ImuDataEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ImuDataEthSettings.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPangleRangeFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPcubicareafilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPintervalFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPmovingAveragingFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPparticle.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LFPradialDistanceRangeFilter.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LSPdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LSPsetdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LoadFactoryDefaults.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LocationName.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/MCSenseLevel.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/OrderNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/RebootDevice.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ScanDataEnable.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ScanDataEthSettings.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/ScanDataFormat.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/SensorPosition.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/SerialNumber.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/SetFieldEvaluationContour.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCRole.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCTCSrvAddr.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCTCtimezone.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCTCupdatetime.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/WriteEeprom.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/mStartMeasure.nlohmann_json.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/mStopMeasure.nlohmann_json.g.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers): magic numbers occur for many
// configuration parameters and result from generated code

namespace sick::multiScan100::v2_4_2_0R {

Configurator::Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password)
  : SensorConfigurator(std::move(httpClient), userLevel, std::move(password))
  , angleRangeFilter(*this)
  , contaminationConfig(*this)
  , contaminationData(*this)
  , contaminationResult(*this)
  , cuboidFilter(*this)
  , sensorTemperature(*this)
  , deviceState(*this)
  , deviceType(*this)
  , distanceFilter(*this)
  , echoFilter(*this)
  , sensorIPAddress(*this)
  , sensorIPAddressingMode(*this)
  , sensorIPMask(*this)
  , sensorIPGateway(*this)
  , ethernetUpdate(*this)
  , fieldEvaluationGroupState(*this)
  , fieldEvaluationResult(*this)
  , firmwareVersion(*this)
  , fogFilter(*this)
  , fieldEvaluationContour(*this)
  , imuStreaming(*this)
  , intervalFilter(*this)
  , locationName(*this)
  , movingAverageFilter(*this)
  , orderNumber(*this)
  , particleFilter(*this)
  , sensorPosition(*this)
  , serialNumber(*this)
  , scanDataStreaming(*this)
  , systemTime(*this)
  , timeSynchronization(*this)
{ }

using C = Configurator;

auto C::ContaminationConfigAccess::get() const -> ContaminationConfiguration
{
  ContaminationConfiguration config;
  config.strategy       = static_cast<uint8_t>(m_configurator.readVariable<api::rest::ContaminationConfig>()._eStrategy);
  config.responseTime   = m_configurator.readVariable<api::rest::ContaminationConfig>()._usiResponseTime.value();
  config.threshold      = static_cast<uint8_t>(m_configurator.readVariable<api::rest::ContaminationConfig>()._eThreshold);
  config.cover          = static_cast<uint8_t>(m_configurator.readVariable<api::rest::ContaminationConfig>()._eCover);
  config.customSectors  = m_configurator.readVariable<api::rest::ContaminationConfig>()._CustomSectors;
  config.bEnableWarning = m_configurator.readVariable<api::rest::ContaminationConfig>()._bEnableWarning;
  config.bEnableError   = m_configurator.readVariable<api::rest::ContaminationConfig>()._bEnableError;

  return config;
}

auto C::ContaminationConfigAccess::set(ContaminationConfiguration const& configuration) const
{
  api::rest::ContaminationConfig::Post::Request req;
  req._eStrategy       = static_cast<api::rest::ContaminationConfig::Post::Request::eStrategy>(configuration.strategy);
  req._usiResponseTime = configuration.responseTime;
  req._eThreshold      = static_cast<api::rest::ContaminationConfig::Post::Request::eThreshold>(configuration.threshold);
  req._eCover          = static_cast<api::rest::ContaminationConfig::Post::Request::eCover>(configuration.cover);
  req._CustomSectors   = configuration.customSectors;
  req._bEnableWarning  = configuration.bEnableWarning;
  req._bEnableError    = configuration.bEnableError;
  m_configurator.writeVariable<api::rest::ContaminationConfig>(req);
}

auto C::ContaminationDataAccess::get() const -> std::vector<int>
{
  return m_configurator.readVariable<api::rest::ContaminationData>()._ContaminationData;
}

auto C::ContaminationResultAccess::get() const -> std::array<bool, 2>
{
  std::array<bool, 2> const arr {
    m_configurator.readVariable<api::rest::ContaminationResult>()._bErrorActive,
    m_configurator.readVariable<api::rest::ContaminationResult>()._bWarningActive
  };
  return arr;
}

// CurrentTempDev
auto C::DeviceTemperatureAccess::get() const -> Temperature
{
  return Temperature::fromDegreesCelsius(m_configurator.readVariable<api::rest::CurrentTempDev>()._CurrentTempDev);
}

// DeviceType
auto C::DeviceTypeAccess::get() const -> std::string
{
  return m_configurator.readVariable<api::rest::DeviceType>()._DeviceType;
}

// EtherIPAddress
auto C::IPAddressAccess::get() const -> IpV4Address
{
  auto const resArray = m_configurator.readVariable<api::rest::EtherIPAddress>()._EtherIPAddress;
  return IpV4Address(std::array<std::uint8_t, 4> {
    static_cast<std::uint8_t>(resArray[0]),
    static_cast<std::uint8_t>(resArray[1]),
    static_cast<std::uint8_t>(resArray[2]),
    static_cast<std::uint8_t>(resArray[3])
  });
}

void C::IPAddressAccess::set(IpV4Address const& ipAddress) const
{
  auto const bytes = ipAddress.bytes();
  api::rest::EtherIPAddress::Post::Request const request {std::array<std::uint8_t, 4> {bytes[0], bytes[1], bytes[2], bytes[3]}};
  m_configurator.writeVariable<api::rest::EtherIPAddress>(request);
}

// EtherIPMask
auto C::IPMaskAccess::get() const -> IpV4Address
{
  auto const mask = m_configurator.readVariable<api::rest::EtherIPMask>()._EtherIPMask;
  return IpV4Address(std::array<std::uint8_t, 4> {
    static_cast<std::uint8_t>(mask[0]),
    static_cast<std::uint8_t>(mask[1]),
    static_cast<std::uint8_t>(mask[2]),
    static_cast<std::uint8_t>(mask[3])
  });
}

void C::IPMaskAccess::set(IpV4Address const& ipMask) const
{
  auto const bytes = ipMask.bytes();
  api::rest::EtherIPMask::Post::Request const request {std::array<std::uint8_t, 4> {bytes[0], bytes[1], bytes[2], bytes[3]}};
  m_configurator.writeVariable<api::rest::EtherIPMask>(request);
}

// EtherIPGateAddress
auto C::IPGatewayAccess::get() const -> IpV4Address
{
  auto const gateway = m_configurator.readVariable<api::rest::EtherIPGateAddress>()._EtherIPGateAddress;
  return IpV4Address(std::array<std::uint8_t, 4> {
    static_cast<std::uint8_t>(gateway[0]),
    static_cast<std::uint8_t>(gateway[1]),
    static_cast<std::uint8_t>(gateway[2]),
    static_cast<std::uint8_t>(gateway[3])
  });
}

void C::IPGatewayAccess::set(IpV4Address const& ipGateway) const
{
  auto const bytes = ipGateway.bytes();
  api::rest::EtherIPGateAddress::Post::Request const request {std::array<std::uint8_t, 4> {bytes[0], bytes[1], bytes[2], bytes[3]}};
  m_configurator.writeVariable<api::rest::EtherIPGateAddress>(request);
}

// EthernetUpdate
void C::EthernetUpdateAccess::apply() const
{
  m_configurator.post(api::rest::EthernetUpdate::methodName).execute();
}

// FieldEvaluationContour
auto C::FieldEvaluationContourAccess::get(std::uint16_t evaluationId) const -> std::vector<FieldEvaluationContour>
{
  api::rest::GetFieldEvaluationContour::Post::Request const request {evaluationId};

  auto const response =
    m_configurator.post(api::rest::GetFieldEvaluationContour::methodName)
      .withPlainRequestPayload(request)
      .execute()
      .withPlainResponsePayload<api::rest::GetFieldEvaluationContour::Post::Response>();

  std::vector<FieldEvaluationContour> ret;
  ret.reserve(response._Contour.size());
  for (auto const& contourItem : response._Contour)
  {
    FieldEvaluationContour contour;
    contour.points.reserve(contourItem._Points.size());
    contour.evaluationId = contourItem._EvaluationId;
    contour.lowerZLimit  = Distance::fromMillimeters(static_cast<float>(contourItem._LowerZLimit.value()));
    contour.upperZLimit  = Distance::fromMillimeters(static_cast<float>(contourItem._UpperZLimit.value()));
    for (auto const& point : contourItem._Points)
    {
      FieldEvaluationContour::Point const newPoint {
        Distance::fromMillimeters(static_cast<float>(point._x)),
        Distance::fromMillimeters(static_cast<float>(point._y))
      };
      contour.points.push_back(newPoint);
    }
    ret.push_back(contour);
  }

  return ret;
}

void C::FieldEvaluationContourAccess::set(std::uint16_t evaluationId, FieldEvaluationContour const& contour) const
{
  NumericRange<std::int32_t, -100000, 100000, 0> const lowerZLimit(static_cast<std::int32_t>(contour.lowerZLimit.millimeters()));
  NumericRange<std::int32_t, -100000, 100000, 0> const upperZLimit(static_cast<std::int32_t>(contour.upperZLimit.millimeters()));
  std::vector<api::rest::SetFieldEvaluationContour::Post::Request::PointsItem> points;
  points.reserve(contour.points.size());
  for (auto const& point : contour.points)
  {
    points.emplace_back(static_cast<std::int32_t>(point.x.millimeters()), static_cast<std::int32_t>(point.y.millimeters()));
  }
  api::rest::SetFieldEvaluationContour::Post::Request const request {evaluationId, points, lowerZLimit, upperZLimit};

  auto const response =
    m_configurator.post(api::rest::SetFieldEvaluationContour::methodName)
      .withPlainRequestPayload(request)
      .execute()
      .withPlainResponsePayload<api::rest::SetFieldEvaluationContour::Post::Response>();

  if (response._ErrorCode != api::rest::SetFieldEvaluationContour::Post::Response::ErrorCode::SopasErrNoErr)
  {
    throw std::runtime_error("Failed to set SetFieldEvaluationContour: " + std::to_string(static_cast<int>(response._ErrorCode)));
  }
}

auto C::FieldEvaluationGroupStateAccess::get() const -> std::array<int, 48>
{
  return m_configurator.readVariable<api::rest::FieldEvaluationGroupState>()._FieldEvaluationGroupState;
}

auto C::FieldEvaluationResultAccess::get() const -> api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult
{
  return m_configurator.readVariable<api::rest::FieldEvaluationResult>()._FieldEvaluationResult;
}

// FirmwareVersion
auto C::FirmwareVersionAccess::get() const -> std::string
{
  return m_configurator.readVariable<api::rest::FirmwareVersion>()._FirmwareVersion;
}

// FogFilter
void C::FogFilterAccess::enable() const
{
  api::rest::MCSenseLevel::Post::Request const request {1};
  m_configurator.writeVariable<api::rest::MCSenseLevel>(request);
}

void C::FogFilterAccess::disable() const
{
  api::rest::MCSenseLevel::Post::Request const request {0};
  m_configurator.writeVariable<api::rest::MCSenseLevel>(request);
}

auto C::FogFilterAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::MCSenseLevel>()._MCSenseLevel.value() != 0;
}

// ImuStreaming
void C::ImuStreamingAccess::configureCompact(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  api::rest::ImuDataEthSettings::Post::Request const request {
    api::rest::ImuDataEthSettings::Post::Request::Protocol::Udp,
    {destinationAddress.bytes().begin(), destinationAddress.bytes().end()},
    destinationPort
  };
  m_configurator.writeVariable<api::rest::ImuDataEthSettings>(request);
}

void C::ImuStreamingAccess::enable() const
{
  api::rest::ImuDataEnable::Post::Request const request {true};
  m_configurator.writeVariable<api::rest::ImuDataEnable>(request);
}

void C::ImuStreamingAccess::disable() const
{
  api::rest::ImuDataEnable::Post::Request const request {false};
  m_configurator.writeVariable<api::rest::ImuDataEnable>(request);
}

auto C::ImuStreamingAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::ImuDataEnable>()._ImuDataEnable;
}

// IntervalFilter
auto C::IntervalFilterAccess::get() const -> NumericRange<std::int32_t, 2, 50, 2>
{
  return m_configurator.readVariable<api::rest::LFPintervalFilter>()._uiReductionFactor;
}

void C::IntervalFilterAccess::enable(NumericRange<std::int32_t, 2, 50, 2> value) const
{
  api::rest::LFPintervalFilter::Post::Request const request {true, value};
  m_configurator.writeVariable<api::rest::LFPintervalFilter>(request);
}

void C::IntervalFilterAccess::disable() const
{
  api::rest::LFPintervalFilter::Post::Request const request {false, {}};
  m_configurator.writeVariable<api::rest::LFPintervalFilter>(request);
}

auto C::IntervalFilterAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPintervalFilter>()._bEnable;
}

// LocationName
auto C::LocationNameAccess::get() const -> std::string
{
  return m_configurator.readVariable<api::rest::LocationName>()._LocationName;
}

void C::LocationNameAccess::set(std::string const& value) const
{
  api::rest::LocationName::Post::Request const request {value};
  m_configurator.writeVariable<api::rest::LocationName>(request);
}

// MovingAverageFilter
auto C::MovingAverageFilterAccess::get() const -> NumericRange<std::uint16_t, 2, 4, 3>
{
  return m_configurator.readVariable<api::rest::LFPmovingAveragingFilter>()._uiAveragingDepth;
}

void C::MovingAverageFilterAccess::enable(NumericRange<std::uint16_t, 2, 4, 3> value) const
{
  api::rest::LFPmovingAveragingFilter::Post::Request const request {true, value};
  m_configurator.writeVariable<api::rest::LFPmovingAveragingFilter>(request);
}

void C::MovingAverageFilterAccess::disable() const
{
  api::rest::LFPmovingAveragingFilter::Post::Request const request {false, {}};
  m_configurator.writeVariable<api::rest::LFPmovingAveragingFilter>(request);
}

auto C::MovingAverageFilterAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPmovingAveragingFilter>()._bEnable;
}

// OrderNumber
auto C::OrderNumberAccess::get() const -> std::string
{
  return m_configurator.readVariable<api::rest::OrderNumber>()._OrderNumber;
}

// ParticleFilter
auto C::ParticleFilterAccess::threshold() const -> Distance
{
  return Distance::fromMillimeters(static_cast<float>(m_configurator.readVariable<api::rest::LFPparticle>()._uiThreshold.value()));
}

void C::ParticleFilterAccess::enable(Distance const& threshold) const
{
  api::rest::LFPparticle::Post::Request const request {true, static_cast<std::uint16_t>(threshold.millimeters())};
  m_configurator.writeVariable<api::rest::LFPparticle>(request);
}

void C::ParticleFilterAccess::disable() const
{
  api::rest::LFPparticle::Post::Request const request {false, {}};
  m_configurator.writeVariable<api::rest::LFPparticle>(request);
}

auto C::ParticleFilterAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPparticle>()._bEnable;
}

// SensorPosition
auto C::SensorPositionAccess::get() const -> SensorPosition
{
  return m_configurator.getSensorPosition<api::rest::SensorPosition>();
}

void C::SensorPositionAccess::set(SensorPosition const& value) const
{
  m_configurator.setSensorPosition<api::rest::SensorPosition>(value);
}

// SerialNumber
auto C::SerialNumberAccess::get() const -> std::string
{
  return m_configurator.readVariable<api::rest::SerialNumber>()._SerialNumber;
}

// ScanDataStreaming
void C::ScanDataStreamingAccess::configureCompact(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  api::rest::ScanDataEthSettings::Post::Request const request {
    api::rest::ScanDataEthSettings::Post::Request::Protocol::Udp,
    {destinationAddress.bytes().begin(), destinationAddress.bytes().end()},
    destinationPort
  };
  m_configurator.writeVariable<api::rest::ScanDataEthSettings>(request);
}

void C::ScanDataStreamingAccess::enable() const
{
  api::rest::ScanDataEnable::Post::Request const request {true};
  m_configurator.writeVariable<api::rest::ScanDataEnable>(request);
}

void C::ScanDataStreamingAccess::disable() const
{
  api::rest::ScanDataEnable::Post::Request const request {false};
  m_configurator.writeVariable<api::rest::ScanDataEnable>(request);
}

auto C::ScanDataStreamingAccess::getMode() const -> StreamingMode
{
  return static_cast<StreamingMode>(m_configurator.readVariable<api::rest::ScanDataFormat>()._ScanDataFormat);
}

auto C::ScanDataStreamingAccess::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::ScanDataEnable>()._ScanDataEnable;
}

void C::ScanDataStreamingAccess::setMode(StreamingMode mode) const
{
  api::rest::ScanDataFormat::Post::Request const request {static_cast<api::rest::ScanDataFormat::Post::Request::ScanDataFormat>(mode)};
  m_configurator.writeVariable<api::rest::ScanDataFormat>(request);
}

// SystemTime
auto C::SystemTimeAccess::get() const -> std::chrono::microseconds
{
  return m_configurator.getSystemTime<api::rest::LSPdatetime>();
}

auto C::SystemTimeAccess::set(std::chrono::microseconds timeSinceEpoch) const -> api::rest::LSPsetdatetime::Post::Response::ErrorCode
{
  return m_configurator.setSystemTime<api::rest::LSPsetdatetime>(timeSinceEpoch);
}

// TimeSynchronization
void C::TimeSynchronizationAccess::disable() const
{
  api::rest::TSCRole::Post::Request const request {api::rest::TSCRole::Post::Request::TSCRole::TxNone};
  m_configurator.writeVariable<api::rest::TSCRole>(request);
}

void C::TimeSynchronizationAccess::enableNtp(
  IpV4Address const& ntpServerAddress,
  api::rest::TSCTCtimezone::Post::Request::TSCTCtimezone timeZone,
  std::chrono::duration<int> updateInterval
) const
{
  {
    api::rest::TSCRole::Post::Request const request {api::rest::TSCRole::Post::Request::TSCRole::TxClient};
    m_configurator.writeVariable<api::rest::TSCRole>(request);
  }
  {
    api::rest::TSCTCSrvAddr::Post::Request const request {{ntpServerAddress.bytes().begin(), ntpServerAddress.bytes().end()}};
    m_configurator.writeVariable<api::rest::TSCTCSrvAddr>(request);
  }
  {
    api::rest::TSCTCtimezone::Post::Request const request {timeZone};
    m_configurator.writeVariable<api::rest::TSCTCtimezone>(request);
  }
  {
    api::rest::TSCTCupdatetime::Post::Request const request {static_cast<std::uint32_t>(std::chrono::seconds(updateInterval).count())};
    m_configurator.writeVariable<api::rest::TSCTCupdatetime>(request);
  }
}

void C::TimeSynchronizationAccess::enablePtp() const
{
  api::rest::TSCRole::Post::Request const request {api::rest::TSCRole::Post::Request::TSCRole::TxPtpSlave};
  m_configurator.writeVariable<api::rest::TSCRole>(request);
}

void Configurator::enableImuStreaming(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  imuStreaming.configureCompact(destinationAddress, destinationPort);
  imuStreaming.enable();
}

void Configurator::enableScanDataStreaming(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const
{
  scanDataStreaming.configureCompact(destinationAddress, destinationPort);
  scanDataStreaming.setMode(StreamingMode::Compact);
  scanDataStreaming.enable();
}

// Sensor methods
void Configurator::factoryReset() const
{
  post(api::rest::LoadFactoryDefaults::methodName).execute();
}

void Configurator::findMe(Duration const& activateFor) const
{
  api::rest::FindMe::Post::Request const request {static_cast<std::uint16_t>(activateFor.seconds())};
  post(api::rest::FindMe::methodName)
    .                                //
    withPlainRequestPayload(request) //
    .execute();
}

void Configurator::reboot() const
{
  post(api::rest::RebootDevice::methodName).execute();
}

void Configurator::startMeasurement() const
{
  auto const response =
    post(api::rest::mStartMeasure::methodName) //
      .execute()                               //
      .withPlainResponsePayload<api::rest::mStartMeasure::Post::Response>();
  if (response._ErrorCode != api::rest::mStartMeasure::Post::Response::ErrorCode::SopasErrNoErr)
  {
    throw std::runtime_error("Failed to start measurement: " + std::to_string(static_cast<int>(response._ErrorCode)));
  }
}

void Configurator::stopMeasurement() const
{
  auto const response =
    post(api::rest::mStopMeasure::methodName) //
      .execute()                              //
      .withPlainResponsePayload<api::rest::mStopMeasure::Post::Response>();
  if (response._ErrorCode != api::rest::mStopMeasure::Post::Response::ErrorCode::SopasErrNoErr)
  {
    throw std::runtime_error("Failed to stop measurement: " + std::to_string(static_cast<int>(response._ErrorCode)));
  }
}

void Configurator::persistParametersOnDevice() const
{
  post(api::rest::WriteEeprom::methodName).execute();
}

} // namespace sick::multiScan100::v2_4_2_0R

namespace sick {

using C       = multiScan100::v2_4_2_0R::Configurator;
namespace api = multiScan100::v2_4_2_0R::api;

// AngleRangeFilter
template <>
auto SDK_EXPORT C::GetAccess<C::AngleRangeFilterSettings>::get() const -> C::AngleRangeFilterSettings
{
  auto const payload = m_configurator.readVariable<api::rest::LFPangleRangeFilter>();
  return C::AngleRangeFilterSettings {
    sopasToAngle(payload._fThetaStart.value()), //
    sopasToAngle(payload._fThetaStop.value()),  //
    payload._uiBeamIncrement                    //
  };
}

template <>
void SDK_EXPORT C::EnableAccess<C::AngleRangeFilterSettings>::enable(C::AngleRangeFilterSettings settings) const
{
  api::rest::LFPangleRangeFilter::Post::Request const
    request {true, angleToSopas(settings.startAzimuth), angleToSopas(settings.stopAzimuth), {}, {}, settings.azimuthIndexIncrement};
  m_configurator.writeVariable<api::rest::LFPangleRangeFilter>(request);
}

template <>
void SDK_EXPORT C::DisableAccess<C::AngleRangeFilterSettings>::disable() const
{
  api::rest::LFPangleRangeFilter::Post::Request const request {false, {}, {}, {}, {}, {}};
  m_configurator.writeVariable<api::rest::LFPangleRangeFilter>(request);
}

template <>
auto SDK_EXPORT C::IsEnabledAccess<C::AngleRangeFilterSettings>::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPangleRangeFilter>()._bEnable;
}

// CuboidFilter
template <>
auto SDK_EXPORT C::GetAccess<C::CuboidFilterSettings>::get() const -> C::CuboidFilterSettings
{
  auto const payload = m_configurator.readVariable<api::rest::LFPcubicareafilter>();
  return C::CuboidFilterSettings {
    {Distance::fromMillimeters(static_cast<float>(payload._lXMin.value())), Distance::fromMillimeters(static_cast<float>(payload._lXMax.value()))},
    {Distance::fromMillimeters(static_cast<float>(payload._lYMin.value())), Distance::fromMillimeters(static_cast<float>(payload._lYMax.value()))},
    {Distance::fromMillimeters(static_cast<float>(payload._lZMin.value())), Distance::fromMillimeters(static_cast<float>(payload._lZMax.value()))}
  };
}

template <>
void SDK_EXPORT C::EnableAccess<C::CuboidFilterSettings>::enable(C::CuboidFilterSettings settings) const
{
  api::rest::LFPcubicareafilter::Post::Request const request {
    true,
    static_cast<int>(settings.x.start.millimeters()),
    static_cast<int>(settings.x.stop.millimeters()),
    static_cast<int>(settings.y.start.millimeters()),
    static_cast<int>(settings.y.stop.millimeters()),
    static_cast<int>(settings.z.start.millimeters()),
    static_cast<int>(settings.z.stop.millimeters())
  };
  m_configurator.writeVariable<api::rest::LFPcubicareafilter>(request);
}

template <>
void SDK_EXPORT C::DisableAccess<C::CuboidFilterSettings>::disable() const
{
  api::rest::LFPcubicareafilter::Post::Request const request {false, {}, {}, {}, {}, {}, {}};
  m_configurator.writeVariable<api::rest::LFPcubicareafilter>(request);
}

template <>
auto SDK_EXPORT C::IsEnabledAccess<C::CuboidFilterSettings>::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPcubicareafilter>()._bEnable;
}

// DeviceState
template <>
auto SDK_EXPORT C::GetAccess<api::rest::DeviceStatus::Get::Response::DeviceStatus>::get() const -> api::rest::DeviceStatus::Get::Response::DeviceStatus
{
  return m_configurator.readVariable<api::rest::DeviceStatus>()._DeviceStatus;
}

// DistanceFilter
template <>
auto SDK_EXPORT C::GetAccess<C::DistanceFilterSettings>::get() const -> C::DistanceFilterSettings
{
  auto const payload = m_configurator.readVariable<api::rest::LFPradialDistanceRangeFilter>();
  return C::DistanceFilterSettings {
    Distance::fromMillimeters(static_cast<float>(payload._ulDistMin.value())),
    Distance::fromMillimeters(static_cast<float>(payload._ulDistMax.value()))
  };
}

template <>
void SDK_EXPORT C::EnableAccess<C::DistanceFilterSettings>::enable(C::DistanceFilterSettings settings) const
{
  api::rest::LFPradialDistanceRangeFilter::Post::Request const request {
    true,
    static_cast<int>(settings.range.start.millimeters()),
    static_cast<int>(settings.range.stop.millimeters())
  };
  m_configurator.writeVariable<api::rest::LFPradialDistanceRangeFilter>(request);
}

template <>
void SDK_EXPORT C::DisableAccess<C::DistanceFilterSettings>::disable() const
{
  api::rest::LFPradialDistanceRangeFilter::Post::Request const request {false, {}, {}};
  m_configurator.writeVariable<api::rest::LFPradialDistanceRangeFilter>(request);
}

template <>
auto SDK_EXPORT C::IsEnabledAccess<C::DistanceFilterSettings>::isEnabled() const -> bool
{
  return m_configurator.readVariable<api::rest::LFPradialDistanceRangeFilter>()._bEnable;
}

// EchoFilter
template <>
auto SDK_EXPORT C::GetAccess<C::EchoFilterSetting>::get() const -> C::EchoFilterSetting
{
  return static_cast<C::EchoFilterSetting>(m_configurator.readVariable<api::rest::FREchoFilter>()._FREchoFilter);
}

template <>
void SDK_EXPORT C::SetAccess<C::EchoFilterSetting>::set(C::EchoFilterSetting value) const
{
  api::rest::FREchoFilter::Post::Request const request {static_cast<api::rest::FREchoFilter::Post::Request::FREchoFilter>(value)};
  m_configurator.writeVariable<api::rest::FREchoFilter>(request);
}

// EtherAddressingMode
template <>
auto SDK_EXPORT C::GetAccess<C::IPAddressingMode>::get() const -> C::IPAddressingMode
{
  return static_cast<C::IPAddressingMode>(m_configurator.readVariable<api::rest::EtherAddressingMode>()._EtherAddressingMode);
}

template <>
void SDK_EXPORT C::SetAccess<C::IPAddressingMode>::set(C::IPAddressingMode mode) const
{
  api::rest::EtherAddressingMode::Post::Request const request {static_cast<api::rest::EtherAddressingMode::Post::Request::EtherAddressingMode>(mode)};
  m_configurator.writeVariable<api::rest::EtherAddressingMode>(request);
}

} // namespace sick

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
