/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <string>
#include <unordered_map>

namespace sick {

#define ENUMERATE_USER_LEVEL                                                                                                                                   \
  __ENUMERATE_USER_LEVEL(Run, 0)                                                                                                                               \
  __ENUMERATE_USER_LEVEL(Operator, 1)                                                                                                                          \
  __ENUMERATE_USER_LEVEL(Maintenance, 2)                                                                                                                       \
  __ENUMERATE_USER_LEVEL(AuthorizedClient, 3)                                                                                                                  \
  __ENUMERATE_USER_LEVEL(Service, 4)                                                                                                                           \
  __ENUMERATE_USER_LEVEL(SICKService, 5)                                                                                                                       \
  __ENUMERATE_USER_LEVEL(Production, 6)                                                                                                                        \
  __ENUMERATE_USER_LEVEL(Developer, 7)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage,bugprone-macro-parentheses)
#define __ENUMERATE_USER_LEVEL(name, value) name = value,
enum class UserLevel
{
  ENUMERATE_USER_LEVEL
};
#undef __ENUMERATE_USER_LEVEL

static std::unordered_map<UserLevel, std::string> const UserLevelToStringMap = {
#define __ENUMERATE_USER_LEVEL(name, value) {UserLevel::name, #name},
  ENUMERATE_USER_LEVEL
#undef __ENUMERATE_USER_LEVEL
};

} // namespace sick
