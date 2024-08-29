/// @file etc.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Internal utilities.
/// @version 1.0
/// @date 2024-08-29
/// @copyright Copyright (c) 2024
export module test:etc;

import std;

/// @brief Testing framework.
export namespace test
{
    /// @brief Test assertion result type.
    class result;

    /// @brief Test runner lambda type that returns test result.
    /// @tparam Lambda Lambda that returns @c test::result .
    template <typename Lambda>
    concept testRunner = requires(Lambda&& lambda)
    {
        { lambda() } -> std::convertible_to<result>;
    };

    /// @brief Reindents multiline messages.
    /// @param[in] string Original text.
    /// @param[in] indentation Target column.
    /// @return Reindented text.
    [[nodiscard]]
    auto reindent(std::string string, const std::size_t indentation) -> std::string
    {
        const std::string nl = "\n";
        const std::string inl = std::vformat("{:{}}", std::make_format_args(nl, indentation));

        std::string::size_type n = 0;
        while ((n = string.find(nl, n)) != std::string::npos)
        {
            string.replace(n, nl.size(), inl);
            n += inl.size();
        }

        return string;
    }

    /// @brief Times function runtime.
    /// @tparam Func Callable function.
    /// @tparam Args Function arguments.
    /// @param[in] func Function to call.
    /// @param[in] args Arguments to pass.
    /// @param[out] time
    /// @return Original functino result.
    template <typename Func, typename... Args>
    [[nodiscard]]
    auto timeit(Func&& func, Args&&... args, std::chrono::duration<long double, std::milli>& time) -> decltype(func(args...))
    {
        using std::chrono::high_resolution_clock;

        const auto start = high_resolution_clock::now();
        auto res = func(std::forward<Args>(args)...);

        time = high_resolution_clock::now() - start;
        return res;
    }
}
