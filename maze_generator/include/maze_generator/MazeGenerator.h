#pragma once
#include <optional>
#include "Settings.h"
#include "../common/Position.h"
#include "../common/Direction.h"
#include "MazeData.h"


namespace Lib {

    class MazeGenerator {
    public:
        explicit MazeGenerator(Settings settings);

        // Generate using backtracking algorithm
        MazeData generate();

        double generationTime() const { return m_generationTime; }

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
        double m_generationTime{ 0 };
    };

}
