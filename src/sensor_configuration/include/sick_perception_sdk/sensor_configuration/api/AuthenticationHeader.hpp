/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <string>

namespace sick {

struct AuthenticationHeader
{
  std::string nonce;
  std::string opaque;
  std::string realm;
  std::string response;
  std::string user;
};

} // namespace sick
