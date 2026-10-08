/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <limits>
#include <stdexcept>
#include <type_traits>

namespace sick {

namespace detail {

template <typename ValueT>
auto checkedAddHelper(ValueT acc) -> ValueT
{
  return acc;
}

template <typename ValueT, typename... RestT>
auto checkedAddHelper(ValueT acc, ValueT next, RestT... rest) -> ValueT
{
  if (acc > (std::numeric_limits<ValueT>::max)() - next)
  {
    throw std::overflow_error("addition would overflow");
  }
  return checkedAddHelper(acc + next, rest...);
}

template <typename ValueT>
auto checkedMultiplyHelper(ValueT acc) -> ValueT
{
  return acc;
}

template <typename ValueT, typename... RestT>
auto checkedMultiplyHelper(ValueT acc, ValueT next, RestT... rest) -> ValueT
{
  if (acc != 0 && next > (std::numeric_limits<ValueT>::max)() / acc)
  {
    throw std::overflow_error("multiplication would overflow");
  }
  return checkedMultiplyHelper(acc * next, rest...);
}

} // namespace detail

template <typename ValueT, typename... ValuesT>
auto checkedAdd(ValueT first, ValueT second, ValuesT... rest) -> ValueT
{
  static_assert(std::is_integral_v<ValueT>, "ValueT must be an integral type");
  static_assert(std::is_unsigned_v<ValueT>, "checkedAdd only supports unsigned integer types");
  static_assert((std::is_same_v<ValueT, ValuesT> && ...), "All value arguments must be the same type");

  if (first > (std::numeric_limits<ValueT>::max)() - second)
  {
    throw std::overflow_error("addition would overflow");
  }
  return detail::checkedAddHelper(first + second, rest...);
}

template <typename ValueT, typename... ValuesT>
auto checkedMultiply(ValueT first, ValueT second, ValuesT... rest) -> ValueT
{
  static_assert(std::is_integral_v<ValueT>, "ValueT must be an integral type");
  static_assert(std::is_unsigned_v<ValueT>, "checkedMultiply only supports unsigned integer types");
  static_assert((std::is_same_v<ValueT, ValuesT> && ...), "All value arguments must be the same type");

  if (first != 0 && second > (std::numeric_limits<ValueT>::max)() / first)
  {
    throw std::overflow_error("multiplication would overflow");
  }
  return detail::checkedMultiplyHelper(first * second, rest...);
}

} // namespace sick
