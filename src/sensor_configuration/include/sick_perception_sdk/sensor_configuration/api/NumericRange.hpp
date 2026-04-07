/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// NOLINTBEGIN(readability-identifier-naming,readability-identifier-length)

#pragma once

#include <cstdint>
#include <nlohmann/json.hpp>
#include <stdexcept>

namespace sick {

template <typename ValueT, ValueT min, ValueT max, ValueT defaultValue>
class NumericRange
{
public:
  constexpr NumericRange()
    : m_value(defaultValue)
  {
    static_assert(defaultValue >= min && defaultValue <= max, "Default value is out of range");
  }

  // NOLINTNEXTLINE(google-explicit-constructor): implicit conversion from ValueT is desired
  constexpr NumericRange(ValueT value)
    : m_value(value)
  {
    if (value < min || value > max)
    {
      throw std::out_of_range("Value " + std::to_string(value) + " is out of range [" + std::to_string(min) + ", " + std::to_string(max) + "]");
    }
  }

  constexpr auto value() const -> ValueT
  {
    return m_value;
  }

private:
  ValueT m_value;
};

template <typename ValueT, ValueT min, ValueT max, ValueT defaultValue>
inline void from_json(nlohmann::json const& j, NumericRange<ValueT, min, max, defaultValue>& r)
{
  ValueT const value = j.get<ValueT>();
  r                  = NumericRange<ValueT, min, max, defaultValue>(value);
}

} // namespace sick

// NOLINTEND(readability-identifier-naming,readability-identifier-length)
