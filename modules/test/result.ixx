/// @file result.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Test result type.
/// @version 1.0
/// @date 2024-08-29
/// @copyright Copyright (c) 2024
export module test:result;

import std;
import ansi;

import :assertable_for;
import :etc;

/// @brief Testing framework.
export namespace test
{
    /// @brief Suit for running tests.
    class suite;

    /// @brief Test assertion result type.
    class result
    {
        friend suite;

    public:
        /// @brief Initializes test result.
        /// @param[in] id ID in the suit.
        /// @param[in] passed Whether the test succeeded.
        /// @param[in] description Test unit description.
        /// @param[in] failDescription Failure description.
        [[nodiscard]]
        result(const std::size_t id, const bool passed, const std::string& description, const std::string& failDescription)
            : m_id(id),
              m_passed(passed),
              m_description(description),
              m_failDescription(failDescription)
        {
        }

#pragma region equals
        /// @returns Integral equality assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto equals(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_equal(returned, expected),
                std::format("{} = {}", returned, expected),
                std::format("Integral equality assertion failed.\nExpected value {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point equality assertion result.
        /// @warning Uses @c operator== to compare.
        [[nodiscard("Result should be returned from the test lambda."), deprecated("Imprecise floating point comparison.")]]
        static auto equals(const std::floating_point auto returned, const std::floating_point auto expected) -> result
        {
            return result(
                LastId++,
                returned == expected,
                std::format("{} = {}", returned, expected),
                std::format("Floating point equality assertion failed.\nExpected value {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point equality assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto equals(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                std::fabs(returned - expected) < epsilon,
                std::format("{} = {}", returned, expected),
                std::format("Floating point equality assertion failed.\nExpected value {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic equality assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto equals(const assertable_for::equals auto& returned, const assertable_for::equals auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned == expected,
                description,
                std::format("Equality assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

#pragma region notEquals
        /// @returns Integral inequality assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto notEquals(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_not_equal(returned, expected),
                std::format("{} ≠ {}", returned, expected),
                std::format("Integral inequality assertion failed.\nExpected value other from {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality assertion result.
        [[nodiscard("Result should be returned from the test lambda."), deprecated("Imprecise floating point comparison.")]]
        static auto notEquals(const std::floating_point auto returned, const std::floating_point auto expected) -> result
        {
            return result(
                LastId++,
                returned != expected,
                std::format("{} ≠ {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value other from {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality assertion result.
        /// @warning Uses @c operator!= to compare.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto notEquals(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                std::fabs(returned - expected) > epsilon,
                std::format("{} ≠ {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value other from {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic inequality assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto notEquals(const assertable_for::notEquals auto& returned, const assertable_for::notEquals auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned != expected,
                description,
                std::format("Inequality assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

#pragma region lessThan
        /// @returns Integral inequality (<) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_less(returned, expected),
                std::format("{} < {}", returned, expected),
                std::format("Integral inequality assertion failed.\nExpected value less than {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality (<) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                returned < expected,
                std::format("{} < {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value less than {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic inequality (<) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan(const assertable_for::lessThan auto& returned, const assertable_for::lessThan auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned < expected,
                description,
                std::format("Inequality (less than) assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

#pragma region lessThan_equals
        /// @returns Integral inequality (<=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan_equals(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_less_equal(returned, expected),
                std::format("{} ≤ {}", returned, expected),
                std::format("Integral inequality assertion failed.\nExpected value less than or equal to {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality (<=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan_equals(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                returned <= expected,
                std::format("{} ≤ {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value less than or equal to {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic inequality (<=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto lessThan_equals(const assertable_for::lessThan_equals auto& returned, const assertable_for::lessThan_equals auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned <= expected,
                description,
                std::format("Inequality (less than or equal to) assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

#pragma region greaterThan
        /// @returns Integral inequality (>) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_greater(returned, expected),
                std::format("{} > {}", returned, expected),
                std::format("Integral inequality assertion failed.\nExpected value greater than {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality (>) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                returned > expected,
                std::format("{} > {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value greater than {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic inequality (>) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan(const assertable_for::greaterThan auto& returned, const assertable_for::greaterThan auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned > expected,
                description,
                std::format("Inequality (greater than) assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

#pragma region greaterThan_equals
        /// @returns Integral inequality (>=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan_equals(const std::integral auto returned, const std::integral auto expected) -> result
        {
            return result(
                LastId++,
                std::cmp_greater_equal(returned, expected),
                std::format("{} ≥ {}", returned, expected),
                std::format("Integral inequality assertion failed.\nExpected value greater than or equal to {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Floating point inequality (>=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan_equals(const std::floating_point auto returned, const std::floating_point auto expected, const std::floating_point auto epsilon) -> result
        {
            return result(
                LastId++,
                returned >= expected,
                std::format("{} ≥ {}", returned, expected),
                std::format("Floating point inequality assertion failed.\nExpected value greater than or equal to {} ({}), but received value {} ({}).", expected, typeid(expected).name(), returned, typeid(returned).name())
            );
        }

        /// @returns Generic inequality (>=) assertion result.
        [[nodiscard("Result should be returned from the test lambda.")]]
        static auto greaterThan_equals(const assertable_for::greaterThan_equals auto& returned, const assertable_for::greaterThan_equals auto& expected, const std::string& description) -> result
        {
            return result(
                LastId++,
                returned >= expected,
                description,
                std::format("Inequality (greater than or equal to) assertion between {} and {} failed.", typeid(expected).name(), typeid(returned).name())
            );
        }
#pragma endregion

    private:
        /// @brief Previously created test result ID.
        static inline std::size_t LastId = 1;

        /// @brief Default-initializes a unit test result.
        result()
            : m_id(0),
              m_passed(false)
        {
        }

        /// @brief Test ID.
        std::size_t m_id;

        /// @brief Whether the assertion resulted in @c true .
        bool m_passed;

        /// @brief Execution time in milliseconds.
        long double m_time = 0;

        /// @brief Unit test descriptions
        std::string m_description, m_failDescription;

        /// @brief Returns the success state of the test.
        explicit inline operator bool() const { return m_passed; }

        /// @brief Reports test information to the standard output.
        auto report() const -> void
        {
            using namespace ansi::manipulators;

            ansi::print<fg::bright::white>("       {}: ", m_id);

            if (m_time > 0)
                ansi::print<text::italic>("{}ms", m_time);

            if (m_passed)
                ansi::println<caret::move(24), fg::gray>(reindent(m_description, 24));
            else
            {
                ansi::println<caret::move(24), fg::red, text::blink>(reindent(m_description, 24));
                ansi::println<caret::move(24), text::italic>(reindent(m_failDescription, 24));
            }
        }
    };
}
