/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/Range.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Temperature.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SensorConfigurator.hpp>
#include <sick_perception_sdk/sensor_configuration/api/FieldEvaluationContour.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/FieldEvaluationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/LSPsetdatetime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/multiScan100/2_4_2_0R/TSCTCtimezone.g.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers): magic numbers result from generated code
// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members): The *Access structs are owned by the configurator thus lifetime is guaranteed by design

namespace sick::multiScan100::v2_4_2_0R {

/**
 * @brief Convenience functions for configuring multiScan100 sensors.
 *
 * This class provides access to common configuration parameters and methods with a consistent naming scheme.
 * Internally, all parameters are mapped to generated data objects in namespace sick::multiScan100::<firmware_version>::api::rest::.
 *
 * See SensorConfigurator for a more detailed description of the design principles.
 */
class SDK_EXPORT Configurator : public SensorConfigurator
{
public:
  struct AngleRangeFilterSettings
  {
    Angle startAzimuth;
    Angle stopAzimuth;
    NumericRange<std::uint16_t, 1, 20, 1> azimuthIndexIncrement;
  };

  struct ContaminationConfiguration
  {
    uint8_t strategy  = 0;
    int responseTime  = 3;
    uint8_t threshold = 0;
    uint8_t cover     = 0;
    std::vector<bool> customSectors {};
    bool bEnableWarning = true;
    bool bEnableError   = true;
  };

  struct CuboidFilterSettings
  {
    Range<Distance> x;
    Range<Distance> y;
    Range<Distance> z;
  };

  struct DistanceFilterSettings
  {
    Range<Distance> range;
  };

  enum class EchoFilterSetting
  {
    FirstEcho = 0,
    AllEchoes = 1,
    LastEcho  = 2,
  };

  enum class IPAddressingMode
  {
    StaticIP = 0,
    DHCP     = 1,
  };

  enum class StreamingMode
  {
    MsgPack     = 1,
    Compact     = 2,
    LmdScanData = 3,
    NativeROS2  = 4,
  };

  class SDK_EXPORT AngleRangeFilterAccess
    : public GetAccess<AngleRangeFilterSettings>
    , public EnableAccess<AngleRangeFilterSettings>
    , public DisableAccess<AngleRangeFilterSettings>
    , public IsEnabledAccess<AngleRangeFilterSettings>
  {
  public:
    explicit AngleRangeFilterAccess(SensorConfigurator const& configurator)
      : GetAccess<AngleRangeFilterSettings>(configurator)
      , EnableAccess<AngleRangeFilterSettings>(configurator)
      , DisableAccess<AngleRangeFilterSettings>(configurator)
      , IsEnabledAccess<AngleRangeFilterSettings>(configurator)
    { }
  };

  class SDK_EXPORT ContaminationConfigAccess
  {
  public:
    explicit ContaminationConfigAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> ContaminationConfiguration;
    auto set(ContaminationConfiguration const& configuration) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT ContaminationDataAccess
  {
  public:
    explicit ContaminationDataAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::vector<int>;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT ContaminationResultAccess
  {
  public:
    explicit ContaminationResultAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::array<bool, 2>;

  private:
    SensorConfigurator const& m_configurator;
  };

  struct CuboidFilterAccess
    : public GetAccess<CuboidFilterSettings>
    , public EnableAccess<CuboidFilterSettings>
    , public DisableAccess<CuboidFilterSettings>
    , public IsEnabledAccess<CuboidFilterSettings>
  {
    explicit CuboidFilterAccess(SensorConfigurator const& configurator)
      : GetAccess<CuboidFilterSettings>(configurator)
      , EnableAccess<CuboidFilterSettings>(configurator)
      , DisableAccess<CuboidFilterSettings>(configurator)
      , IsEnabledAccess<CuboidFilterSettings>(configurator)
    { }
  };

  class SDK_EXPORT DeviceTemperatureAccess
  {
  public:
    explicit DeviceTemperatureAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> Temperature;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT DeviceTypeAccess
  {
  public:
    explicit DeviceTypeAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::string;

  private:
    SensorConfigurator const& m_configurator;
  };

  struct DistanceFilterAccess
    : public GetAccess<DistanceFilterSettings>
    , public EnableAccess<DistanceFilterSettings>
    , public DisableAccess<DistanceFilterSettings>
    , public IsEnabledAccess<DistanceFilterSettings>
  {
    explicit DistanceFilterAccess(SensorConfigurator const& configurator)
      : GetAccess<DistanceFilterSettings>(configurator)
      , EnableAccess<DistanceFilterSettings>(configurator)
      , DisableAccess<DistanceFilterSettings>(configurator)
      , IsEnabledAccess<DistanceFilterSettings>(configurator)
    { }
  };

  class SDK_EXPORT IPAddressAccess
  {
  public:
    explicit IPAddressAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> IpV4Address;
    void set(IpV4Address const& ipAddress) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT IPMaskAccess
  {
  public:
    explicit IPMaskAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> IpV4Address;
    void set(IpV4Address const& ipMask) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT IPGatewayAccess
  {
  public:
    explicit IPGatewayAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> IpV4Address;
    void set(IpV4Address const& ipGateway) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT EthernetUpdateAccess
  {
  public:
    explicit EthernetUpdateAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void apply() const;

  private:
    SensorConfigurator const& m_configurator;
  };

  //Field Evaluation
  class SDK_EXPORT FieldEvaluationGroupStateAccess
  {
  public:
    explicit FieldEvaluationGroupStateAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::array<int, 48>;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT FieldEvaluationResultAccess
  {
  public:
    explicit FieldEvaluationResultAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> api::rest::FieldEvaluationResult::Get::Response::FieldEvaluationResult;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT ImuStreamingAccess
  {
  public:
    explicit ImuStreamingAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void configureCompact(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
    void disable() const;
    void enable() const;
    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT FieldEvaluationContourAccess
  {
  public:
    explicit FieldEvaluationContourAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void set(std::uint16_t evaluationId, FieldEvaluationContour const& contour) const;
    auto get(std::uint16_t evaluationId) const -> std::vector<FieldEvaluationContour>;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT FirmwareVersionAccess
  {
  public:
    explicit FirmwareVersionAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::string;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT FogFilterAccess
  {
  public:
    explicit FogFilterAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void enable() const;
    void disable() const;
    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT IntervalFilterAccess
  {
  public:
    explicit IntervalFilterAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> NumericRange<std::int32_t, 2, 50, 2>;
    auto enable(NumericRange<std::int32_t, 2, 50, 2> value) const -> void;
    auto disable() const -> void;
    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT LocationNameAccess
  {
  public:
    explicit LocationNameAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::string;
    void set(std::string const& value) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  // This works until somebody else needs this NumericRange specialization as payload
  class SDK_EXPORT MovingAverageFilterAccess
  {
  public:
    explicit MovingAverageFilterAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> NumericRange<std::uint16_t, 2, 4, 3>;
    auto enable(NumericRange<std::uint16_t, 2, 4, 3> value) const -> void;
    auto disable() const -> void;
    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT OrderNumberAccess
  {
  public:
    explicit OrderNumberAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::string;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT ParticleFilterAccess
  {
  public:
    explicit ParticleFilterAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto threshold() const -> Distance;
    auto enable(Distance const& threshold) const -> void;
    auto disable() const -> void;
    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT ScanDataStreamingAccess
  {
  public:
    explicit ScanDataStreamingAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void configureCompact(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
    void disable() const;
    void enable() const;
    auto getMode() const -> StreamingMode;
    auto isEnabled() const -> bool;
    void setMode(StreamingMode mode) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT SerialNumberAccess
  {
  public:
    explicit SerialNumberAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::string;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT SensorPositionAccess
  {
  public:
    explicit SensorPositionAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> SensorPosition;
    void set(SensorPosition const& value) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT StreamingAccess
  {
  public:
    explicit StreamingAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void configureCompact(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
    void disable() const;
    void enable() const;
    auto getMode() const -> StreamingMode;
    auto isEnabled() const -> bool;
    void setMode(StreamingMode mode) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  class SDK_EXPORT SystemTimeAccess
  {
  public:
    explicit SystemTimeAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::chrono::microseconds;
    auto set(std::chrono::microseconds timeSinceEpoch) const -> api::rest::LSPsetdatetime::Post::Response::ErrorCode;

  private:
    SensorConfigurator const& m_configurator;
  };

  struct TimeSynchronizationAccess
  {
  public:
    explicit TimeSynchronizationAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void disable() const;
    void enableNtp(
      IpV4Address const& ntpServerAddress,
      api::rest::TSCTCtimezone::Post::Request::TSCTCtimezone timeZone,
      std::chrono::duration<int> updateInterval
    ) const;
    void enablePtp() const;

  private:
    SensorConfigurator const& m_configurator;
  };

  explicit Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);
  ~Configurator()                                      = default;
  Configurator(Configurator const&)                    = delete;
  auto operator=(Configurator const&) -> Configurator& = delete;
  Configurator(Configurator&&)                         = delete;
  auto operator=(Configurator&&) -> Configurator&      = delete;

  // Public const members provide a fluent API (e.g., configurator.sensorTemperature.get()).
  // Since they are const, external mutation is not possible, making this safe.
  // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
  AngleRangeFilterAccess const angleRangeFilter;

  ContaminationConfigAccess const contaminationConfig;

  ContaminationDataAccess const contaminationData;

  ContaminationResultAccess const contaminationResult;

  CuboidFilterAccess const cuboidFilter;

  DeviceTemperatureAccess const sensorTemperature;

  GetAccess<api::rest::DeviceStatus::Get::Response::DeviceStatus> const deviceState;

  DeviceTypeAccess const deviceType;

  DistanceFilterAccess const distanceFilter;

  GetSetAccess<EchoFilterSetting> const echoFilter;

  IPAddressAccess const sensorIPAddress;

  GetSetAccess<IPAddressingMode> const sensorIPAddressingMode;

  IPMaskAccess const sensorIPMask;

  IPGatewayAccess const sensorIPGateway;

  EthernetUpdateAccess const ethernetUpdate;

  FirmwareVersionAccess const firmwareVersion;

  FogFilterAccess const fogFilter;

  ImuStreamingAccess imuStreaming;

  IntervalFilterAccess const intervalFilter;

  LocationNameAccess const locationName;

  MovingAverageFilterAccess const movingAverageFilter;

  OrderNumberAccess const orderNumber;

  ParticleFilterAccess const particleFilter;

  ScanDataStreamingAccess const scanDataStreaming;

  SensorPositionAccess const sensorPosition;

  SerialNumberAccess const serialNumber;

  // Field Evaluation

  FieldEvaluationGroupStateAccess const fieldEvaluationGroupState;

  FieldEvaluationResultAccess const fieldEvaluationResult;

  FieldEvaluationContourAccess const fieldEvaluationContour;

  /**
   * @brief Access to the current system time of the sensor. The system time is represented as a duration since the
   * sensor's epoch (Unix epoch).
   */
  SystemTimeAccess const systemTime;

  TimeSynchronizationAccess const timeSynchronization;
  // NOLINTEND(misc-non-private-member-variables-in-classes)

  void enableImuStreaming(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;
  void enableScanDataStreaming(IpV4Address const& destinationAddress, std::uint16_t destinationPort) const;

  // Sensor methods
  void factoryReset() const;
  void findMe(Duration const& activateFor) const;
  void reboot() const;
  void startMeasurement() const;
  void stopMeasurement() const;
  void persistParametersOnDevice() const;
};

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace sick::multiScan100::v2_4_2_0R
