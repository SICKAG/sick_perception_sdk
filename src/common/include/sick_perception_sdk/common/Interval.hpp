/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <utility>

namespace sick {

/**
 * @brief A class that represents a numeric interval. A value can be checked if it is in the interval with contains().
 * 
 * If the interval is empty all values (including NaN for floating-point types) will be considered inside the interval.
 * If the interval is not empty NaN values will be considered outside the interval for floating-point types.
 */
template <typename T>
class Interval
{
public:
  Interval()
    : m_limits(std::nullopt)
  { }

  explicit Interval(T min, T max, bool invert)
    : m_limits(std::make_pair(min, max))
    , m_invert(invert)
  { }

  /**
   * @brief Check if the value is in the range [min, max].
   * 
   * If invert is true, the result is inverted.
   */
  auto contains(T value) const -> bool
  {
    if (!m_limits.has_value())
    {
      return true;
    }
    auto const [min, max] = m_limits.value();
    bool const inRange    = (value >= min) && (value <= max);
    return m_invert ? !inRange : inRange;
  }

  /**
   * @brief Check if the range is empty, i.e. there is a value that can be in the range.
   * 
   * If the range is not configured (both min and max are not set) it is considered empty.
   */
  auto isEmpty() const -> bool
  {
    if (m_limits.has_value())
    {
      auto const [min, max] = m_limits.value();
      return min >= max;
    }
    return true;
  }

  auto toString() const -> std::string
  {
    std::ostringstream result;
    result << (m_invert ? "not " : "");
    if (m_limits.has_value())
    {
      auto const [min, max] = m_limits.value();
      result << "[" << min << ", " << max << "]";
    }
    else
    {
      result << "[-inf, +inf]";
    }
    return result.str();
  }

private:
  std::optional<std::pair<T, T>> m_limits;
  bool m_invert {false};
};

} // namespace sick
