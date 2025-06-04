#pragma once
#include <vector>
#include "Settings.h"
#include <optional>
#include "../common/Cell.h"
#include "../common/Position.h"
#include "../common/Direction.h"


class MazeGenerator {
public:
    explicit MazeGenerator(Settings settings);

    struct MazeData {
        std::vector<std::vector<Cell>> matrix;
        Position enter;
        Position exit;
        double generationTime{};
    };

    // Generate using backtracking algorithm
    MazeData generate();

private: /* Helper methods used for generating matrix */
    void carvePath(Position pos, Direction dir);

    // Returns a random valid direction from the given position
    std::optional<Direction> randomDirection(Position pos);

    // Checks if a path can be carved from the given position in a direction
    bool isValidDirection(Position pos);

    // Randomly add items across the maze
    void placeItems();

    // Clear a path in the second-to-last row and carve some additional passages
    void carveAdditionalPassages();

private: /* Data */
    Settings m_settings;
    MazeData m_data;
};
