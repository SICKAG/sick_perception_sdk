---
applyTo: "**/*.*pp"
---

Take the clang tidy rules into account when generating or modifying c++ code. You can find the rules in the file `.clang-tidy` in the repository root.

Do not write pointless documentation. Document only functions and classes if their name does not make it obvious what they do.

Use Doxygen style comments with block comments (`/** ... */`) instead of line comments (`/// ...`) for documentation. Use the `@` notation for doxygen tags. For example:

```cpp
/**
 * @brief Computes the factorial of a number.
 * @param n The number to compute the factorial of.
 * @return The factorial of n.
 * @throws std::invalid_argument if n is negative.
 */
int factorial(int n);
```

In contrast to classes or functions use inline comments (`///< ...`) in doxygen documentation for members. For example:

```cpp
struct PointCloud {
    std::size_t width; ///< Number of columns (organized) or total points (unorganized)
    std::size_t height; ///< Number of rows (organized) or 1 (unorganized)
};
```

Always place a comma after the last element of an enum.

Be as const correct as possible, i.e. if something can be `const`, make it `const`. This applies to member functions, parameters and variables.

If something describes the size or number of a collection prefix the name with `numberOf`.

The names of unit tests should describe the tested function and the expected behavior. The case for test case names is `snake_case`. The test class name should describe the tested class with a `Test` suffix. For example:

```cpp
TEST(PointCloudBuilderTest, build_builds_point_cloud_with_correct_fields) {
    // Test implementation
}
```

Our c++ code can use features of c++17 or older, but not features of c++20 or newer. Do not use features that are only available in c++20 or newer. For example, do not use concepts or the `[[nodiscard]]` attribute.

Use trailing return types for all functions returning values other than void.

Prefer expressive template names instead of single letter template names and add the `T` suffix. For example, use `typename ValueT` instead of `typename T` and `typename ContainerT` instead of `typename C`.
