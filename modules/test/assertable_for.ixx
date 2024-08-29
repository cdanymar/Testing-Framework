/// @file assertable_for.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Internal concepts.
/// @version 1.0
/// @date 2024-08-29
/// @copyright Copyright (c) 2024
export module test:assertable_for;

import std;

/// @brief Conceptual tests and conditions for assertable values.
export namespace assertable_for
{
    /// @brief Asserting requirements for @c assert::equals .
    /// @tparam Type must exhibit @c operator== .
    template <typename T>
    concept equals = requires(const T& lhs, const T& rhs)
    {
        { lhs == rhs } -> std::same_as<bool>;
    };

    /// @brief Asserting requirements for @c assert::notEquals .
    /// @tparam Type must exhibit @c operator!= .
    template <typename T>
    concept notEquals = requires(const T& lhs, const T& rhs)
    {
        { lhs != rhs } -> std::same_as<bool>;
    };

    /// @brief Asserting requirements for @c assert::lessThan .
    /// @tparam Type must exhibit @c operator< .
    template <typename T>
    concept lessThan = requires(const T& lhs, const T& rhs)
    {
        { lhs < rhs } -> std::same_as<bool>;
    };

    /// @brief Asserting requirements for @c assert::lessThan_equals .
    /// @tparam Type must exhibit @c operator<= .
    template <typename T>
    concept lessThan_equals = requires(const T& lhs, const T& rhs)
    {
        { lhs <= rhs } -> std::same_as<bool>;
    };

    /// @brief Asserting requirements for @c assert::greaterThan .
    /// @tparam Type must exhibit @c operator> .
    template <typename T>
    concept greaterThan = requires(const T& lhs, const T& rhs)
    {
        { lhs > rhs } -> std::same_as<bool>;
    };

    /// @brief Asserting requirements for @c assert::greaterThan_equals .
    /// @tparam Type must exhibit @c operator>= .
    template <typename T>
    concept greaterThan_equals = requires(const T& lhs, const T& rhs)
    {
        { lhs >= rhs } -> std::same_as<bool>;
    };
}
