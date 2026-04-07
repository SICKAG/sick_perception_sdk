/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Temperature.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/SensorConfigurator.hpp>
#include <sick_perception_sdk/sensor_configuration/api/FieldEvaluationContour.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/DeviceStatus.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/FieldEvaluationResult.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/TSCTCtimezone.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/LRS4000/1_9_1_0R/mSetDateTime.g.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers): magic numbers result from generated code
// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members): The *Access structs are owned by the configurator thus lifetime is guaranteed by design

namespace sick::LRS4000::v1_9_1_0R {

/**
 * @brief Convenience functions for configuring LRS4000 sensors.
 *
 * This class provides access to common configuration parameters and methods with a consistent naming scheme.
 * Internally, all parameters are mapped to generated data objects in namespace sick::LRS4000::<firmware_version>::api::rest::.
 *
 * See SensorConfigurator for a more detailed description of the design principles.
 */
class SDK_EXPORT Configurator : public SensorConfigurator
{
public:
  struct ContaminationConfiguration
  {
    uint8_t strategy  = 0;
    int responseTime  = 3;
    uint8_t threshold = 0;
    uint8_t cover     = 0;
    std::array<bool, 12> customSectors {};
    bool bEnableWarning = true;
    bool bEnableError   = true;
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
    Disabled    = 0,
    Compact     = 2,
    LMDscandata = 3,
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

    auto get() const -> std::array<int, 12>;

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

  class SDK_EXPORT SystemTimeAccess
  {
  public:
    explicit SystemTimeAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> std::chrono::microseconds;
    auto set(std::chrono::microseconds timeSinceEpoch) const -> api::rest::mSetDateTime::Post::Response::ErrorCode;

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

  explicit Configurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string const& password);
  ~Configurator()                                      = default;
  Configurator(Configurator const&)                    = delete;
  auto operator=(Configurator const&) -> Configurator& = delete;
  Configurator(Configurator&&)                         = delete;
  auto operator=(Configurator&&) -> Configurator&      = delete;

  // Public const members provide a fluent API (e.g., configurator.sensorTemperature.get()).
  // Since they are const, external mutation is not possible, making this safe.
  // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
  ContaminationConfigAccess const contaminationConfig;

  ContaminationDataAccess const contaminationData;

  ContaminationResultAccess const contaminationResult;

  DeviceTemperatureAccess const sensorTemperature;

  GetAccess<api::rest::DeviceStatus::Get::Response::DeviceStatus> const deviceState;

  DeviceTypeAccess const deviceType;

  IPAddressAccess const sensorIPAddress;

  GetSetAccess<IPAddressingMode> const sensorIPAddressingMode;

  IPMaskAccess const sensorIPMask;

  IPGatewayAccess const sensorIPGateway;

  EthernetUpdateAccess const ethernetUpdate;

  GetSetAccess<EchoFilterSetting> const echoFilter;

  FirmwareVersionAccess const firmwareVersion;

  LocationNameAccess const locationName;

  OrderNumberAccess const orderNumber;

  SerialNumberAccess const serialNumber;

  GetSetAccess<StreamingMode> const streaming;

  // 2D Object Detection - Field Evaluation

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

  // Device methods
  void factoryReset() const;
  void findMe(Duration const& activateFor) const;
  void reboot() const;
  void startMeasurement() const;
  void persistParametersOnDevice() const;
};

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace sick::LRS4000::v1_9_1_0R
