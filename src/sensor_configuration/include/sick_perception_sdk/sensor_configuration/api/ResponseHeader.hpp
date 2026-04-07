/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <string>

namespace sick {

struct ResponseHeader
{
  int status {-1};
  std::string message;
};

} // namespace sick
