/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @defgroup Quantities Physical Quantities
 *
 * Physical quantities like distance or timestamps are represented by strong types in order to avoid
 * mixing up different units or quantities.
 *
 * ## Creation and Value Access
 * 
 * Quantity objects are created by static functions indicating their unit and scaling, e.g. `Duration::fromMilliseconds()`.
 * The contained value is accessed by member functions indicating the unit and scale, e.g. `Duration::microseconds()`.
 *
 * @note Note that the provided classes are not complete by design. They only provide the functionality needed for the SDK.
 * If new functionality is required, it may be implemented in addition to the existing code.
 *
 * ## Unit Conversions
 * 
 * If a conversion from one quantity to another is necessary, the quantity classes should provide appropriate member functions or operators.
 * A common example is the difference of two `Timestamp`s which results in a `Duration`.
 * @warning Manual conversion using the member access (e.g. `Quantity(otherQuantity.value() * some value)`) is discouraged because it is error-prone
 * and hinders code readability. Prefer using dedicated conversion functions instead and implement missing conversions if necessary.
 *
 * ## Literals
 * 
 * Some quantities provide literals for convenient creation of quantity objects. The literals all start with an underscore (`_`) 
 * to avoid potential name clashes with standard C++ literals.
 * 
 * The literals are defined in the `sick::literals` namespace.
 * 
 * ## Internal Representation
 * 
 * @note Some quantities are designed so that they can be used in data structures that are filled with `std::memcpy`. A common use case for this 
 * is the deserialization of Compact formats. In this use case the calling code relies on the internal representation convention of the quantities.
 * Therefore:
 * - a quantity's internal representation (data type, scaling) must not be changed.
 * - A quantity **must not contain additional value members**. Adding new functions is permissible but the size of the object instance in memory must not change.
 *
 * @note Some quantities provide mutable access to their internal representation via `rawValueMutable()`. This is intended to be used for some deserialization
 * contexts using `std::memcpy` and should not be used otherwise.
 */
