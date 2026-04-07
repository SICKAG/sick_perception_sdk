/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace sick {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

/**
 * @brief A lightweight, non-owning view over contiguous byte data (header-only implementation).
 *
 * This class provides a span-like interface for C++17, making it easier to work with
 * byte ranges without copying. All implementations are inline in the header.
 */
class ByteView
{
public:
  using value_type      = std::uint8_t;
  using pointer         = std::uint8_t const*;
  using const_pointer   = std::uint8_t const*;
  using reference       = std::uint8_t const&;
  using const_reference = std::uint8_t const&;
  using iterator        = std::uint8_t const*;
  using const_iterator  = std::uint8_t const*;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  ByteView() = delete;

  ByteView(std::uint8_t const* data, std::size_t size)
    : m_data(data)
    , m_size(size)
  { }

  // NOLINTNEXTLINE(google-explicit-constructor)
  ByteView(std::vector<std::uint8_t> const& vec)
    : m_data(vec.data())
    , m_size(vec.size())
  { }

  auto data() const noexcept -> std::uint8_t const*
  {
    return m_data;
  }

  auto size() const noexcept -> std::size_t
  {
    return m_size;
  }

  auto empty() const noexcept -> bool
  {
    return m_size == 0;
  }

  /**
   * @brief Accesses the byte at the specified index without bounds checking.
   * 
   * @note Accessing an out-of-range index or if the internal data pointer is nullptr results in undefined behavior (similar to std::vector::operator[]).
   */
  auto operator[](std::size_t index) const -> std::uint8_t
  {
    // Axivion Next Line CertC++-EXP34 : nullptr dereference follows the same logic as std::vector::operator[].
    return m_data[index];
  }

  auto at(std::size_t index) const -> std::uint8_t
  {
    if (m_data == nullptr || index >= m_size)
    {
      throw std::out_of_range("ByteView::at: index out of range");
    }
    return m_data[index];
  }

  auto begin() const noexcept -> std::uint8_t const*
  {
    return m_data;
  }

  auto end() const noexcept -> std::uint8_t const*
  {
    return m_data + m_size;
  }

  auto cbegin() const noexcept -> std::uint8_t const*
  {
    return m_data;
  }

  auto cend() const noexcept -> std::uint8_t const*
  {
    return m_data + m_size;
  }

  auto front() const -> std::uint8_t
  {
    if (m_data == nullptr || m_size == 0)
    {
      throw std::out_of_range("ByteView::front: view is empty");
    }
    return m_data[0];
  }

  auto back() const -> std::uint8_t
  {
    if (m_data == nullptr || m_size == 0)
    {
      throw std::out_of_range("ByteView::back: view is empty");
    }
    return m_data[m_size - 1];
  }

  auto subview(std::size_t offset) const -> ByteView
  {
    if (offset > m_size)
    {
      throw std::out_of_range("ByteView::subview: offset out of range");
    }
    return {m_data + offset, m_size - offset};
  }

  auto subview(std::size_t offset, std::size_t count) const -> ByteView
  {
    if (offset > m_size)
    {
      throw std::out_of_range("ByteView::subview: offset out of range");
    }
    if (offset + count > m_size)
    {
      throw std::out_of_range("ByteView::subview: count out of range");
    }
    return {m_data + offset, count};
  }

  auto first(std::size_t count) const -> ByteView
  {
    if (count > m_size)
    {
      throw std::out_of_range("ByteView::first: count out of range");
    }
    return {m_data, count};
  }

  auto last(std::size_t count) const -> ByteView
  {
    if (count > m_size)
    {
      throw std::out_of_range("ByteView::last: count out of range");
    }
    return {m_data + m_size - count, count};
  }

  auto toVector() const -> std::vector<std::uint8_t>
  {
    // NOLINTNEXTLINE(modernize-return-braced-init-list): let's be explicit here and not rely on the initializer list.
    return std::vector<std::uint8_t>(m_data, m_data + m_size);
  }

private:
  std::uint8_t const* m_data = nullptr;
  std::size_t m_size         = 0;
};

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

} // namespace sick
