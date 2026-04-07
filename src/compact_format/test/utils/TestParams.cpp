/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "TestParams.hpp"

namespace sick::test {

// Overloading the << operator prevents access to uninitialized memory in gtest (valgrind).
auto operator<<(std::ostream& os, TestParams const& params) -> std::ostream&
{
  os << "device: " << params.device << ", fileIdentifier: " << params.fileIdentifier;
  return os;
}

} // namespace sick::test
