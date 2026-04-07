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
  constexpr BitField()
    : m_value {static_cast<EnumT>(0)}
  { }

  constexpr explicit BitField(EnumT value)
    : m_value {value}
  { }

  constexpr explicit BitField(std::underlying_type_t<EnumT> value)
    : m_value {static_cast<EnumT>(value)}
  { }

  constexpr auto isEmpty() const -> bool
  {
    return m_value == static_cast<EnumT>(0);
  }

  constexpr auto isSet(EnumT mask) const -> bool
  {
    return static_cast<std::underlying_type_t<EnumT>>(m_value & mask) == static_cast<std::underlying_type_t<EnumT>>(mask);
  }

  constexpr auto isSet(BitField<EnumT> const& mask) const -> bool
  {
    return isSet(mask.m_value);
  }

  constexpr auto isUnset(EnumT mask) const -> bool
  {
    return static_cast<std::underlying_type_t<EnumT>>(m_value & mask) == 0;
  }

  constexpr auto isUnset(BitField<EnumT> const& mask) const -> bool
  {
    return isUnset(mask.m_value);
  }

  constexpr void set(EnumT mask)
  {
    m_value = m_value | mask;
  }

  constexpr void unset(EnumT mask)
  {
    m_value = static_cast<EnumT>(static_cast<std::underlying_type_t<EnumT>>(m_value) & ~static_cast<std::underlying_type_t<EnumT>>(mask));
  }

  constexpr auto value() const -> EnumT
  {
    return m_value;
  }

private:
  EnumT m_value;
};

} // namespace sick
