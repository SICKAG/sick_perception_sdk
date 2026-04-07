/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cmath>
#include <limits>
#include <ostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace sick {

/**
 * @ingroup Quantities
 * 
 * See quantities.hpp for an overview.
 */
class SDK_EXPORT Angle
{
public:
  using value_type = float;

  constexpr Angle()
    : m_radians(std::numeric_limits<Angle::value_type>::quiet_NaN())
  { }

  constexpr static auto fromDegrees(Angle::value_type degrees) -> Angle
  {
    return Angle(degrees * static_cast<Angle::value_type>(M_PI) / 180.0f);
  }

  constexpr static auto fromRadians(Angle::value_type rad) -> Angle
  {
    return Angle(rad);
  }

  constexpr auto degrees() const -> Angle::value_type
  {
    return m_radians * static_cast<Angle::value_type>(180.0f / M_PI);
  }

  constexpr auto radians() const -> Angle::value_type
  {
    return m_radians;
  }

  /**
   * @brief Mutable access to the raw value.
   *
   * @warning Use this function with caution. It relies on convention what the internal representation is.
   * Therefore, this function should only be used for deserialization of Compact formats.
   */
  constexpr auto rawValueMutable() -> Angle::value_type&
  {
    return m_radians;
  }

private:
  /**
   * @brief The internal representation of the quantity's value.
   * 
   * @warning This member must be the same type and scaling as in the Compact format!
   */
  value_type m_radians;

  constexpr explicit Angle(value_type rad)
    : m_radians {rad}
  { }
};

// Comparison operators
constexpr auto operator<(Angle const& lhs, Angle const& rhs) -> bool
{
  return lhs.radians() < rhs.radians();
}

constexpr auto operator<=(Angle const& lhs, Angle const& rhs) -> bool
{
  return lhs.radians() <= rhs.radians();
}

constexpr auto operator>(Angle const& lhs, Angle const& rhs) -> bool
{
  return lhs.radians() > rhs.radians();
}

constexpr auto operator>=(Angle const& lhs, Angle const& rhs) -> bool
{
  return lhs.radians() >= rhs.radians();
}

// Arithmetic operators
constexpr auto operator+(Angle const& lhs, Angle const& rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() + rhs.radians());
}

constexpr auto operator-(Angle const& lhs, Angle const& rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() - rhs.radians());
}

constexpr auto operator-(Angle const& angle) -> Angle
{
  return Angle::fromRadians(-angle.radians());
}

/**
 * Multiplication with a non-Angle scalar is useful for forming multiples of an angle and are therefore only implemented for integers.
 */
constexpr auto operator*(Angle const& lhs, int rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() * static_cast<Angle::value_type>(rhs));
}

/**
 * Multiplication with a non-Angle scalar is useful for forming multiples of an angle and are therefore only implemented for integers.
 */
constexpr auto operator*(Angle const& lhs, unsigned int rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() * static_cast<Angle::value_type>(rhs));
}

/**
 * Multiplication with a non-Angle scalar is useful for forming multiples of an angle and are therefore only implemented for integers.
 */
constexpr auto operator*(Angle const& lhs, std::size_t rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() * static_cast<Angle::value_type>(rhs));
}

/**
 * Division by a non-Angle scalar is useful for forming partial angles and are therefore only implemented for integers.
 */
constexpr auto operator/(Angle const& lhs, unsigned int rhs) -> Angle
{
  return Angle::fromRadians(lhs.radians() / static_cast<Angle::value_type>(rhs));
}

// Stream operators
auto SDK_EXPORT operator<<(std::ostream& stream, Angle const& angle) -> std::ostream&;

namespace literals {

constexpr auto operator"" _deg(long double value) -> Angle
{
  return Angle::fromDegrees(static_cast<Angle::value_type>(value));
}

constexpr auto operator"" _deg(unsigned long long value) -> Angle
{
  return Angle::fromDegrees(static_cast<Angle::value_type>(value));
}

constexpr auto operator"" _rad(long double value) -> Angle
{
  return Angle::fromRadians(static_cast<Angle::value_type>(value));
}

constexpr auto operator"" _rad(unsigned long long value) -> Angle
{
  return Angle::fromRadians(static_cast<Angle::value_type>(value));
}

} // namespace literals

auto SDK_EXPORT sin(Angle const& angle) -> float;
auto SDK_EXPORT cos(Angle const& angle) -> float;

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Angle const& angle) -> std::string;

} // namespace std

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
