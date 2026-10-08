/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// NOLINTBEGIN(readability-identifier-naming,readability-identifier-length)

#pragma once

#include <cstdint>
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

// The JSON type is a template parameter so this public header does not depend on <nlohmann/json.hpp>.
// The body is only instantiated in the (private) serialization translation units, which include the
// full nlohmann/json definition. ADL still finds this overload for NumericRange members.
template <typename BasicJsonT, typename ValueT, ValueT min, ValueT max, ValueT defaultValue>
inline void from_json(BasicJsonT const& j, NumericRange<ValueT, min, max, defaultValue>& r)
{
  r = NumericRange<ValueT, min, max, defaultValue>(j.template get<ValueT>());
}

} // namespace sick

// NOLINTEND(readability-identifier-naming,readability-identifier-length)
