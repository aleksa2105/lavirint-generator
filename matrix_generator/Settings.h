#pragma once
#include <stdexcept>

/* Define your settings here */

constexpr int minRows{ 15 };
constexpr int maxRows{ 75 };

constexpr int minCols{ 15 };
constexpr int maxCols{ 75 };

constexpr int minItems{ 3 };
constexpr int maxItems{ 30 };

/* ------------------------- */

struct Settings {
    int numRows{};
    int numCols{};
    int numItems{};
};

inline Settings handleArguments(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::invalid_argument("Error: Invalid number of arguments (4 expected)");
    }

    try {
        int numRows{ std::stoi(argv[1]) };
        int numCols{ std::stoi(argv[2]) };
        int numItems{ std::stoi(argv[3]) };

        if (numRows > maxRows || numRows < minRows ||
            numCols > maxCols || numCols < minCols ||
            numItems > maxItems || numItems < minItems) {
            throw std::out_of_range("Error: Argument out of bounds");
        }

        return Settings{ numRows, numCols, numItems };
    }
    catch (const std::invalid_argument&) {
        throw std::invalid_argument("Error: Invalid type of arguments (integer expected)");
    }
}