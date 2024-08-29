/// @file suite.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Suite of tests.
/// @version 1.0
/// @date 2024-08-29
/// @copyright Copyright (c) 2024
export module test:suite;

export import :result;
import :etc;

/// @brief Testing framework.
export namespace test
{
    /// @brief Contains and runs unit tests.
    class suite final
    {
    public:
        /// @brief Initializes new suite of unit tests.
        /// @param[in] title Suite title.
        /// @param[in] lambdas Test result lambdas.
        /// @see test::result
        explicit suite(const std::string_view title, testRunner auto&&... lambdas)
            : suite(title, "", std::forward<decltype(lambdas)>(lambdas)...)
        {
        }

        /// @brief Initializes new suite of unit tests.
        /// @param[in] title Suite title.
        /// @param[in] description Suite description.
        /// @param[in] lambdas Test result lambdas.
        /// @see test::result
        explicit suite(const std::string_view title, const std::string description, testRunner auto&&... lambdas)
        {
            using namespace ansi::manipulators;

            (execute(lambdas), ...);

            m_failed.empty()
                ? ansi::print<fg::bright::green, text::bold>("[SUCCESS] ")
                : ansi::print<fg::bright::red, text::bold, text::blink>("[FAILURE] ");

            ansi::println<fg::bright::white>(title);

            if (!description.empty())
                ansi::println("          {}", reindent(description, 10));

            if (!m_passed.empty())
            {
                ansi::print<fg::bright::white>("\n     Test Passed: ");
                ansi::println<fg::bright::green, text::bold>("{}/{}", m_passed.size(), sizeof...(lambdas));

                for (const auto& passed : m_passed)
                    passed.report();
            }

            if (!m_failed.empty())
            {
                ansi::print<fg::bright::white>("\n     Test Failed: ");
                ansi::println<fg::bright::red, text::bold>("{}/{}", m_failed.size(), sizeof...(lambdas));

                for (const auto& failed : m_failed)
                    failed.report();
            }

            ansi::println();
            result::LastId = 1;
        }

    private:
        /// @brief Suite tests.
        std::vector<result> m_passed, m_failed;

        /// @param runner Test lambda to execute.
        /// @returns Lambda's result.
        auto execute(testRunner auto&& runner) -> bool
        {
            std::chrono::duration<long double, std::milli> time;
            result test = timeit(runner, time);
            test.m_time = time.count();

            const bool passed = static_cast<bool>(test);
            std::vector<result>& tests = passed ? m_passed : m_failed;

            tests.push_back(test);
            return passed;
        }
    };
}
