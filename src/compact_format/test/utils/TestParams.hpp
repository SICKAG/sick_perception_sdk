/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <ostream>
#include <string>

namespace sick::test {

struct TestParams
{
  std::string device         = "";
  std::string fileIdentifier = ""; // Not always a file path ;)

  friend std::ostream& operator<<(std::ostream& os, TestParams const& params);
};

} // namespace sick::test
