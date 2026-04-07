/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>

namespace sick::compact {

auto SDK_EXPORT crc32Impl(ByteView data) -> std::uint32_t;

} // namespace sick::compact
