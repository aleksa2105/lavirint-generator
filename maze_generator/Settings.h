#pragma once
#include <stdexcept>

/* Define your settings here */

constexpr int g_minRows{ 15 };
constexpr int g_maxRows{ 75 };

constexpr int g_minCols{ 15 };
constexpr int g_maxCols{ 75 };

constexpr int g_minItems{ 3 };
constexpr int g_maxItems{ 30 };

constexpr int g_consoleLines{ 25 }; // number of new lines for console clearing

/* ------------------------- */

struct Settings {
    int numRows{};
    int numCols{};
    int numItems{};
};

// function used to check validity and create settings from console line arguments
inline Settings handleArguments(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::invalid_argument("Error: Invalid number of arguments (4 expected: executable, number of rows, number of columns, number of items)");
    }

    try {
        int numRows{ std::stoi(argv[1]) };
        int numCols{ std::stoi(argv[2]) };
        int numItems{ std::stoi(argv[3]) };

        if (numRows > g_maxRows || numRows < g_minRows ||
            numCols > g_maxCols || numCols < g_minCols ||
            numItems > g_maxItems || numItems < g_minItems) {
            throw std::out_of_range("Error: Argument out of bounds (lookup maze_generator/Settings.h for valid argument values)");
        }

        return Settings{ numRows, numCols, numItems };
    }
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Error: Invalid type of arguments (integers expected)");
    }
}