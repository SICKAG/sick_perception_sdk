/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/sensor_configuration/HttpClient/IHttpClient.hpp>
#include <sick_perception_sdk/sensor_configuration/RestClient/RestClient.hpp>
#include <sick_perception_sdk/sensor_configuration/api/AuthenticationHeader.hpp>
#include <sick_perception_sdk/sensor_configuration/api/Challenge.hpp>
#include <sick_perception_sdk/sensor_configuration/api/SensorPosition.hpp>
#include <sick_perception_sdk/sensor_configuration/api/UserLevel.hpp>

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)

namespace sick {

/**
 * @brief Base class for sensor-specific sensor configurator classes.
 */
class SDK_EXPORT SensorConfigurator
{
public:
  /**
   * @brief Construct a new configurator object.
   *
   * The parameters will be stored and used for all read, write, and invoke requests. Constructing this object is cheap,
   * so a new instance should be created when a different set of parameters is required.
   *
   * @param httpClient The HTTP client to use for communication with the sensor.
   * @param userLevel The user level to use for authentication when performing POST requests (for `post` and `writeVariable`).
   * @param password The password to use for authentication when performing POST requests (for `post` and `writeVariable`).
   */
  explicit SensorConfigurator(std::shared_ptr<IHttpClient> httpClient, UserLevel userLevel, std::string password);
  ~SensorConfigurator() = default;

  SensorConfigurator(SensorConfigurator const&)                    = delete;
  auto operator=(SensorConfigurator const&) -> SensorConfigurator& = delete;
  SensorConfigurator(SensorConfigurator&&)                         = delete;
  auto operator=(SensorConfigurator&&) -> SensorConfigurator&      = delete;

  // --------------------------------------------------
  // Convenience Accessors
  // --------------------------------------------------

  /**
   * @brief Basic accessor for getting a variable value from the sensor.
   *
   * @tparam ReturnT Note that this type must be unique within the cmake project. This accessor is therefore only useful
   * for unique types like enums or sensor-specific structures. Basic types like `int` or `std::string` are not suitable
   * for this accessor because they would create duplicate types for two different accessor instances.
   */
  template <class ReturnT>
  class GetAccess
  {
  public:
    explicit GetAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto get() const -> ReturnT;

  private:
    SensorConfigurator const& m_configurator;
  };

  /**
   * @brief Basic accessor for setting a variable on the sensor.
   *
   * @tparam ReturnT Note that this type must be unique within the cmake project. This accessor is therefore only useful
   * for unique types like enums or sensor-specific structures. Basic types like `int` or `std::string` are not suitable
   * for this accessor because they would create duplicate types for two different accessor instances.
   */
  template <class ParamT>
  class SetAccess
  {
  public:
    explicit SetAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void set(ParamT value) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  /**
   * @brief Basic accessor for getting a variable value from and setting a variable on the sensor.
   *
   * @tparam ReturnT Note that this type must be unique within the cmake project. This accessor is therefore only useful
   * for unique types like enums or sensor-specific structures. Basic types like `int` or `std::string` are not suitable
   * for this accessor because they would create duplicate types for two different accessor instances.
   */
  template <class T>
  struct GetSetAccess
    : public GetAccess<T>
    , public SetAccess<T>
  {
  public:
    explicit GetSetAccess(SensorConfigurator const& configurator)
      : GetAccess<T>(configurator)
      , SetAccess<T>(configurator)
    { }
  };

  /**
   * @brief Basic accessor for enabling an entity on the sensor.
   *
   * @tparam Args Parameter types to pass to `enable`. Note that these types must be unique within the cmake project.
   * This accessor is therefore only useful for unique types like enums or sensor-specific structures. Basic types like
   * `int` or `std::string` are not suitable for this accessor because they would create duplicate types for two
   * different accessor instances.
   */
  template <typename... Args>
  class EnableAccess
  {
  public:
    explicit EnableAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void enable(Args... args) const;

  private:
    SensorConfigurator const& m_configurator;
  };

  /**
   * @brief Basic accessor for disabling an entity on the sensor.
   *
   * @tparam T Type to uniquely identify an accessor. Note that these types must be unique within the cmake project.
   * This accessor is therefore only useful for unique types like enums or sensor-specific structures. Basic types like
   * `int` or `std::string` are not suitable for this accessor because they would create duplicate types for two
   * different accessor instances.
   */
  template <typename T>
  class DisableAccess
  {
  public:
    explicit DisableAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    void disable() const;

  private:
    SensorConfigurator const& m_configurator;
  };

  /**
   * @brief Basic accessor for checking if an entity on the sensor is enabled.
   *
   * @tparam T Type to uniquely identify an accessor. Note that this type must be unique within the cmake project. This
   * accessor is therefore only useful for unique types like enums or sensor-specific structures. Basic types like `int`
   * or `std::string` are not suitable for this accessor because they would create duplicate types for two different
   * accessor instances.
   */
  template <typename T>
  class IsEnabledAccess
  {
  public:
    explicit IsEnabledAccess(SensorConfigurator const& configurator)
      : m_configurator(configurator)
    { }

    auto isEnabled() const -> bool;

  private:
    SensorConfigurator const& m_configurator;
  };

  /**
   * @brief Base function to read the sensor position.
   *
   * @tparam Derived classes must provide the appropriate payload type (typically `sick::<sensor type>::<firmware_version>::api::rest::SensorPosition`).
   */
  template <class PayloadT>
  auto getSensorPosition() const -> SensorPosition
  {
    auto const response = readVariable<PayloadT>();
    SensorPosition ret {
      Distance::fromMillimeters(static_cast<float>(response._x.value())), //
      Distance::fromMillimeters(static_cast<float>(response._y.value())), //
      Distance::fromMillimeters(static_cast<float>(response._z.value())), //
      sopasToAngle(response._yaw.value()),                                //
      sopasToAngle(response._pitch.value()),                              //
      sopasToAngle(response._roll.value()),                               //
    };
    return ret;
  }

  /**
   * @brief Base function to set the sensor position.
   *
   * @tparam Derived classes must provide the appropriate payload type (typically `sick::<sensor type>::<firmware_version>::api::rest::SensorPosition`).
   */
  template <class PayloadT>
  void setSensorPosition(SensorPosition const& position) const
  {
    typename PayloadT::Post::Request const request {
      static_cast<std::int32_t>(position.x.millimeters()), //
      static_cast<std::int32_t>(position.y.millimeters()), //
      static_cast<std::int32_t>(position.z.millimeters()), //
      angleToSopas(position.yaw),                          //
      angleToSopas(position.pitch),                        //
      angleToSopas(position.roll),                         //
    };
    writeVariable<PayloadT>(request);
  }

  /**
   * @brief Get the current system time of the sensor.
   *
   * @tparam PayloadT Derived classes must provide the appropriate payload type (typically `sick::<sensor type>::<firmware_version>::api::rest::LSPdatetime`).
   */
  template <class PayloadT>
  auto getSystemTime() const -> std::chrono::microseconds
  {
    auto const sickDatetime = readVariable<PayloadT>()._LSPdatetime;

    std::tm timeStruct {};
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    timeStruct.tm_year = static_cast<int>(sickDatetime._uiYear.value()) - 1900;
    timeStruct.tm_mon  = static_cast<int>(sickDatetime._usiMonth.value()) - 1;
    timeStruct.tm_mday = static_cast<int>(sickDatetime._usiDay.value());
    timeStruct.tm_hour = static_cast<int>(sickDatetime._usiHour.value());
    timeStruct.tm_min  = static_cast<int>(sickDatetime._usiMinute.value());
    timeStruct.tm_sec  = static_cast<int>(sickDatetime._usiSec.value());

#ifdef _WIN32
    time_t const secondsSinceEpoch = _mkgmtime(&timeStruct);
#else
    time_t const secondsSinceEpoch = timegm(&timeStruct);
#endif

    return std::chrono::seconds(static_cast<std::int64_t>(secondsSinceEpoch)) +
           std::chrono::microseconds(static_cast<std::int64_t>(sickDatetime._udiUSec.value()));
  }

  /**
   * @brief Set the current system time of the sensor.
   *
   * @param timeSinceEpoch The time to set, expressed as microseconds since the Unix epoch (1970-01-01T00:00:00Z).
   *
   * @tparam PayloadT Derived classes must provide the appropriate payload type (typically `sick::<sensor type>::<firmware_version>::api::rest::LSPsetdatetime`, **not** `sick::<sensor type>::<firmware_version>::api::rest::LSPdatetime`!).
   */
  template <class PayloadT>
  auto setSystemTime(std::chrono::microseconds timeSinceEpoch) const -> typename PayloadT::Post::Response::ErrorCode
  {
    auto seconds      = std::chrono::duration_cast<std::chrono::seconds>(timeSinceEpoch);
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(timeSinceEpoch - seconds);

    std::time_t const timeT = seconds.count();
    std::tm timeStruct {};

#ifdef _WIN32
    errno_t err = gmtime_s(&timeStruct, &timeT);
    if (err != 0)
    {
      throw std::runtime_error("Failed to convert time to UTC");
    }
#else
    if (gmtime_r(&timeT, &timeStruct) == nullptr)
    {
      throw std::runtime_error("Failed to convert time to UTC");
    }
#endif

    typename PayloadT::Post::Request::DateTime sickDateTime;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    sickDateTime._uiYear    = static_cast<std::uint16_t>(timeStruct.tm_year) + 1900;
    sickDateTime._usiMonth  = static_cast<std::uint8_t>(timeStruct.tm_mon) + 1;
    sickDateTime._usiDay    = static_cast<std::uint8_t>(timeStruct.tm_mday);
    sickDateTime._usiHour   = static_cast<std::uint8_t>(timeStruct.tm_hour);
    sickDateTime._usiMinute = static_cast<std::uint8_t>(timeStruct.tm_min);
    sickDateTime._usiSec    = static_cast<std::uint8_t>(timeStruct.tm_sec);
    sickDateTime._udiUSec   = static_cast<std::uint32_t>(microseconds.count());

    typename PayloadT::Post::Request const request {sickDateTime};
    auto const ret =
      post(PayloadT::methodName) //
        .withRequestPayload("DateTime", sickDateTime)
        .execute()
        .template withPlainResponsePayload<typename PayloadT::Post::Response>()
        ._ErrorCode;
    return ret;
  }

  // --------------------------------------------------
  // Raw Variable Access
  // --------------------------------------------------
  /**
   * @brief Read a variable from the sensor via REST.
   *
   * This will perform a GET request to the sensor.
   *
   * @tparam ReturnT The expected return type. The type must provide the sub-type `ReturnT::Get::Response`,
   * the value `PayloadT::variableName`, and the value `PayloadT::isSopasMethod`.
   */
  template <class PayloadT>
  auto readVariable() const -> typename PayloadT::Get::Response
  {
    static_assert(!PayloadT::isSopasMethod, "PayloadT must not represent a SOPAS method!");
    return m_client.get<typename PayloadT::Get::Response>(PayloadT::variableName);
  }

  /**
   * @brief Write a variable to the sensor via REST.
   *
   * @tparam PayloadT The type of the payload to write. The type must provide the sub-type `PayloadT::Post::Request`,
   * the value `PayloadT::variableName`, and the value `PayloadT::isSopasMethod`.
   */
  template <class PayloadT>
  void writeVariable(typename PayloadT::Post::Request const& payload) const
  {
    static_assert(!PayloadT::isSopasMethod, "PayloadT must not represent a SOPAS method!");
    m_client.post(PayloadT::variableName)
      .withAuthentication(getAuthenticationHeader(PayloadT::variableName, getChallenge()))
      .withRequestPayload(PayloadT::variableName, payload)
      .execute();
  }

  /**
   * @brief Provide raw access to a post request.
   *
   * This should primarily be used for invoking SOPAS methods.
   * 
   * In other cases this function should be used very carefully in case the structure of an endpoint's 
   * POST request or response is very specific. 
   * 
   * See PostRequest for details.
   */
  auto post(std::string const& endpoint) const -> PostRequest;

protected:
  auto getAuthenticationHeader(std::string const& variableName, Challenge const& challenge) const -> AuthenticationHeader;
  auto getChallenge() const -> Challenge;

private:
  std::string m_userLevelStr;
  std::string m_password;

  RestClient m_client;
};

} // namespace sick

// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
