/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/IpV4Address.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

namespace sick {

// AXIVION Next Construct CertC++-STR32: this ctor is not 100% safe. The implications are documented in the header.
IpV4Address::IpV4Address(char const* str)
  : IpV4Address {std::string(str, strlen(str))}
{ }

IpV4Address::IpV4Address(std::string const& str)
  : m_bytes {0, 0, 0, 0}
{
  if (str.empty())
  {
    throw std::invalid_argument("Input string is empty");
  }

  try
  {
    std::istringstream stream(str);
    std::string segment;

    std::size_t segmentIndex = 0;
    while (std::getline(stream, segment, '.'))
    {
      if (segmentIndex > 3)
      {
        throw std::out_of_range("Input string is too long");
      }

      int const octet = std::stoi(segment);
      if (octet < 0 || octet > std::numeric_limits<std::uint8_t>::max())
      {
        throw std::out_of_range("Octet out of range");
      }

      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index): segmentIndex is checked above
      m_bytes[segmentIndex] = octet;
      segmentIndex++;
    }

    if (segmentIndex != 4)
    {
      throw std::out_of_range("Input string is too short");
    }
  }
  catch (std::exception const& exception)
  {
    auto const message = std::string("Invalid IP address format: ") + exception.what();
    throw std::invalid_argument(message);
  }
}

IpV4Address::IpV4Address(std::array<std::uint8_t, 4> bytes)
  : m_bytes(bytes)
{ }

auto IpV4Address::toString() const -> std::string
{
  return std::to_string(m_bytes[0]) + "." + std::to_string(m_bytes[1]) + "." + std::to_string(m_bytes[2]) + "." + std::to_string(m_bytes[3]);
}

} // namespace sick
