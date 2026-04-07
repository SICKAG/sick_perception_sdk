/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/ByteView.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

using namespace sick;

TEST(ByteView, constructor_from_pointer_and_size_creates_view)
{
  std::uint8_t const data[] = {1, 2, 3, 4, 5};
  ByteView const view(data, 5);

  EXPECT_EQ(data, view.data());
  EXPECT_EQ(5, view.size());
  EXPECT_FALSE(view.empty());
}

TEST(ByteView, constructor_from_vector_creates_view)
{
  std::vector<std::uint8_t> const data = {10, 20, 30};
  ByteView const view(data);

  EXPECT_EQ(data.data(), view.data());
  EXPECT_EQ(3, view.size());
  EXPECT_FALSE(view.empty());
}

TEST(ByteView, constructor_from_empty_vector_creates_empty_view)
{
  std::vector<std::uint8_t> const data;
  ByteView const view(data);

  EXPECT_EQ(0, view.size());
  EXPECT_TRUE(view.empty());
}

TEST(ByteView, subscript_operator_returns_element_at_index)
{
  std::vector<std::uint8_t> const data = {5, 10, 15, 20};
  ByteView const view(data);

  EXPECT_EQ(5, view[0]);
  EXPECT_EQ(10, view[1]);
  EXPECT_EQ(15, view[2]);
  EXPECT_EQ(20, view[3]);
}

TEST(ByteView, at_returns_element_at_valid_index)
{
  std::vector<std::uint8_t> const data = {100, 200};
  ByteView const view(data);

  EXPECT_EQ(100, view.at(0));
  EXPECT_EQ(200, view.at(1));
}

TEST(ByteView, at_throws_on_out_of_range_index)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.at(3), std::out_of_range);
  EXPECT_THROW(view.at(100), std::out_of_range);
}

TEST(ByteView, at_throws_on_empty_view)
{
  std::vector<std::uint8_t> const data;
  ByteView const view(data);

  EXPECT_THROW(view.at(0), std::out_of_range);
}

TEST(ByteView, begin_and_end_enable_iteration)
{
  std::vector<std::uint8_t> const data = {1, 2, 3, 4};
  ByteView const view(data);

  std::vector<std::uint8_t> result(view.begin(), view.end());

  EXPECT_EQ(data, result);
}

TEST(ByteView, cbegin_and_cend_enable_const_iteration)
{
  std::vector<std::uint8_t> const data = {5, 6, 7};
  ByteView const view(data);

  std::vector<std::uint8_t> result(view.cbegin(), view.cend());

  EXPECT_EQ(data, result);
}

TEST(ByteView, range_based_for_loop_iterates_all_elements)
{
  std::vector<std::uint8_t> const data = {10, 20, 30};
  ByteView const view(data);

  std::vector<std::uint8_t> result;
  for (auto const byte : view)
  {
    result.push_back(byte);
  }

  EXPECT_EQ(data, result);
}

TEST(ByteView, front_returns_first_element)
{
  std::vector<std::uint8_t> const data = {42, 100, 200};
  ByteView const view(data);

  EXPECT_EQ(42, view.front());
}

TEST(ByteView, back_returns_last_element)
{
  std::vector<std::uint8_t> const data = {42, 100, 200};
  ByteView const view(data);

  EXPECT_EQ(200, view.back());
}

TEST(ByteView, subview_with_offset_creates_view_of_suffix)
{
  std::vector<std::uint8_t> const data = {1, 2, 3, 4, 5};
  ByteView const view(data);

  ByteView const sub = view.subview(2);

  EXPECT_EQ(3, sub.size());
  EXPECT_EQ(3, sub[0]);
  EXPECT_EQ(4, sub[1]);
  EXPECT_EQ(5, sub[2]);
}

TEST(ByteView, subview_with_offset_equal_to_size_creates_empty_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const sub = view.subview(3);

  EXPECT_TRUE(sub.empty());
  EXPECT_EQ(0, sub.size());
}

TEST(ByteView, subview_with_zero_offset_creates_full_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const sub = view.subview(0);

  EXPECT_EQ(3, sub.size());
  EXPECT_EQ(view.data(), sub.data());
}

TEST(ByteView, subview_with_offset_throws_when_out_of_range)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.subview(4), std::out_of_range);
}

TEST(ByteView, subview_with_offset_and_count_creates_middle_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3, 4, 5};
  ByteView const view(data);

  ByteView const sub = view.subview(1, 3);

  EXPECT_EQ(3, sub.size());
  EXPECT_EQ(2, sub[0]);
  EXPECT_EQ(3, sub[1]);
  EXPECT_EQ(4, sub[2]);
}

TEST(ByteView, subview_with_zero_count_creates_empty_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const sub = view.subview(1, 0);

  EXPECT_TRUE(sub.empty());
}

TEST(ByteView, subview_with_offset_and_count_throws_when_offset_out_of_range)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.subview(4, 1), std::out_of_range);
}

TEST(ByteView, subview_with_offset_and_count_throws_when_count_out_of_range)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.subview(1, 3), std::out_of_range);
}

TEST(ByteView, first_creates_view_of_prefix)
{
  std::vector<std::uint8_t> const data = {10, 20, 30, 40, 50};
  ByteView const view(data);

  ByteView const prefix = view.first(3);

  EXPECT_EQ(3, prefix.size());
  EXPECT_EQ(10, prefix[0]);
  EXPECT_EQ(20, prefix[1]);
  EXPECT_EQ(30, prefix[2]);
}

TEST(ByteView, first_with_zero_count_creates_empty_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const prefix = view.first(0);

  EXPECT_TRUE(prefix.empty());
}

TEST(ByteView, first_with_full_size_returns_equivalent_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const prefix = view.first(3);

  EXPECT_EQ(3, prefix.size());
  EXPECT_EQ(view.data(), prefix.data());
}

TEST(ByteView, first_throws_when_count_exceeds_size)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.first(4), std::out_of_range);
}

TEST(ByteView, last_creates_view_of_suffix)
{
  std::vector<std::uint8_t> const data = {10, 20, 30, 40, 50};
  ByteView const view(data);

  ByteView const suffix = view.last(2);

  EXPECT_EQ(2, suffix.size());
  EXPECT_EQ(40, suffix[0]);
  EXPECT_EQ(50, suffix[1]);
}

TEST(ByteView, last_with_zero_count_creates_empty_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const suffix = view.last(0);

  EXPECT_TRUE(suffix.empty());
}

TEST(ByteView, last_with_full_size_returns_equivalent_view)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  ByteView const suffix = view.last(3);

  EXPECT_EQ(3, suffix.size());
  EXPECT_EQ(view.data(), suffix.data());
}

TEST(ByteView, last_throws_when_count_exceeds_size)
{
  std::vector<std::uint8_t> const data = {1, 2, 3};
  ByteView const view(data);

  EXPECT_THROW(view.last(4), std::out_of_range);
}

TEST(ByteView, to_vector_creates_copy_of_data)
{
  std::vector<std::uint8_t> const data = {5, 10, 15, 20};
  ByteView const view(data);

  std::vector<std::uint8_t> const copy = view.toVector();

  EXPECT_EQ(data, copy);
  EXPECT_NE(data.data(), copy.data());
}

TEST(ByteView, to_vector_from_empty_view_returns_empty_vector)
{
  std::vector<std::uint8_t> const data;
  ByteView const view(data);

  std::vector<std::uint8_t> const copy = view.toVector();

  EXPECT_TRUE(copy.empty());
}

TEST(ByteView, iterator_difference_equals_size)
{
  std::vector<std::uint8_t> const data = {1, 2, 3, 4, 5};
  ByteView const view(data);

  auto const diff = view.end() - view.begin();

  EXPECT_EQ(5, diff);
}

TEST(ByteView, std_algorithms_work_with_iterators)
{
  std::vector<std::uint8_t> const data = {3, 1, 4, 1, 5};
  ByteView const view(data);

  auto const minElement = std::min_element(view.begin(), view.end());
  auto const maxElement = std::max_element(view.begin(), view.end());
  auto const count      = std::count(view.begin(), view.end(), 1);

  EXPECT_EQ(1, *minElement);
  EXPECT_EQ(5, *maxElement);
  EXPECT_EQ(2, count);
}

