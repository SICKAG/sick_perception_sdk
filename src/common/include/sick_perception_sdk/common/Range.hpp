/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

namespace sick {

template <class ValueT>
struct SDK_EXPORT Range
{
  ValueT start;
  ValueT stop;
};

} // namespace sick
