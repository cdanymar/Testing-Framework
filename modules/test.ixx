/// @file test.ixx
/// @author Danylo Marchenko (cdanymar)
/// @brief Minimal testing framework.
/// @version 1.0
/// @date 2024-08-29
/// @copyright Copyright (c) 2024
export module test;

export import :suite;

/// @brief Shortcut for asserting results.
export using assert = test::result;
