/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <type_traits>

namespace sick {

template <typename EnumT>
constexpr auto operator|(EnumT lhs, EnumT rhs) -> EnumT
{
  static_assert(std::is_enum_v<EnumT>, "BitField requires an enum type");
  using T = std::underlying_type_t<EnumT>;
  return static_cast<EnumT>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

template <typename EnumT>
constexpr auto operator&(EnumT lhs, EnumT rhs) -> EnumT
{
  static_assert(std::is_enum_v<EnumT>, "BitField requires an enum type");
  using T = std::underlying_type_t<EnumT>;
  return static_cast<EnumT>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

template <typename EnumT>
class BitField
{
  static_assert(std::is_enum_v<EnumT>, "BitField requires an enum type");

public:
  using UnderlyingT = std::underlying_type_t<EnumT>;

  constexpr BitField()
    : m_value {static_cast<UnderlyingT>(0)}
  { }

  constexpr explicit BitField(EnumT value)
    : m_value {static_cast<UnderlyingT>(value)}
  { }

  constexpr explicit BitField(std::underlying_type_t<EnumT> value)
    : m_value {value}
  { }

  constexpr explicit BitField(unsigned value)
    : m_value {static_cast<UnderlyingT>(value)}
  { }

  constexpr auto isEmpty() const -> bool
  {
    return m_value == 0;
  }

  constexpr auto isSet(EnumT mask) const -> bool
  {
    return (m_value & static_cast<UnderlyingT>(mask)) == static_cast<UnderlyingT>(mask);
  }

  constexpr auto isSet(BitField<EnumT> const& mask) const -> bool
  {
    return isSet(mask.m_value);
  }

  constexpr auto isUnset(EnumT mask) const -> bool
  {
    return (m_value & static_cast<UnderlyingT>(mask)) == 0;
  }

  constexpr auto isUnset(BitField<EnumT> const& mask) const -> bool
  {
    return isUnset(mask.m_value);
  }

  constexpr void set(EnumT mask)
  {
    m_value = m_value | static_cast<UnderlyingT>(mask);
  }

  constexpr void set(EnumT mask, bool value)
  {
    if (value)
    {
      set(mask);
    }
    else
    {
      unset(mask);
    }
  }

  constexpr void unset(EnumT mask)
  {
    m_value = m_value & ~static_cast<UnderlyingT>(mask);
  }

  constexpr auto underlyingValue() const -> UnderlyingT
  {
    return static_cast<UnderlyingT>(m_value);
  }

  constexpr auto operator==(BitField const& other) const -> bool
  {
    return m_value == other.m_value;
  }

  constexpr auto operator!=(BitField const& other) const -> bool
  {
    return m_value != other.m_value;
  }

private:
  UnderlyingT m_value;
};

} // namespace sick
