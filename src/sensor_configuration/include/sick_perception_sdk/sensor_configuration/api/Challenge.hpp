/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include "ResponseHeader.hpp"

#include <stdint.h>
#include <string>
#include <vector>

namespace sick {

struct Challenge
{
  ResponseHeader header;
  std::string nonce;
  std::string opaque;
  std::string realm;
  std::vector<std::uint8_t> salt;
};

} // namespace sick
