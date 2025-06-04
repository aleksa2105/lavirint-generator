#include "MazeGenerator.h"
#include <chrono>
#include "../utils/Random.h"
#include "../common/Direction.h"
#include <stack>


MazeGenerator::MazeGenerator(Settings settings)
    : m_settings{ settings } {
    m_data.matrix = std::vector(settings.numRows, std::vector(settings.numCols, Cell::wall)); // initially fill with walls
}

MazeGenerator::MazeData MazeGenerator::generate() {
    const auto startTime = std::chrono::system_clock::now(); // track generation time

    // randomly select position for enterance
    m_data.enter = Position{ Random::get(1, m_settings.numCols - 2), 0 };
    m_data.matrix[m_data.enter.y][m_data.enter.x] = Cell::enter;

    // randomly select position for exit
    m_data.exit = Position{ Random::get(1, m_settings.numCols - 2), m_settings.numRows - 1 };
    m_data.matrix[m_data.exit.y][m_data.exit.x] = Cell::exit;

    std::stack<Position> backtrack;

    Position startPos{ m_data.enter.x, 1 }; // starting position for generating passages
    backtrack.push(startPos);
    // addPath(startPos, Direction{ 0, 0 });

    while (!backtrack.empty()) {
        Position pos{ backtrack.top() };
        std::optional<Direction> dir{ randomDirection(pos) };

        if (!dir.has_value()) // no direction was available for that position
            backtrack.pop();
        else {
            pos.x += dir.value().dx;
            pos.y += dir.value().dy;
            carvePath(pos, dir.value());
            backtrack.push(pos);
        }
    }

    carveAdditionalPassages();
    placeItems();

    const auto endTime{ std::chrono::system_clock::now() }; // mark time
    m_data.generationTime = std::chrono::duration(endTime - startTime).count();

    return m_data;
}

void MazeGenerator::carvePath(Position pos, Direction dir) {
    m_data.matrix[pos.y][pos.x] = Cell::passage;
    m_data.matrix[pos.y - dir.dy / 2][pos.x - dir.dx / 2] = Cell::passage; // in opposite direction than dir, mark cell as path
}

std::optional<Direction> MazeGenerator::randomDirection(Position pos) {
    std::vector<Direction> directions;
    if (isValidDirection(Position{ pos.x, pos.y - 2 })) { directions.emplace_back(0, -2); } // north
    if (isValidDirection(Position{ pos.x, pos.y + 2 })) { directions.emplace_back(0, 2); } // south
    if (isValidDirection(Position{ pos.x - 2, pos.y })) { directions.emplace_back(-2, 0); } // west
    if (isValidDirection(Position{ pos.x + 2, pos.y })) { directions.emplace_back(2, 0); } // east

    if (directions.empty()) {
        // no directions are available
        return std::nullopt;
    }

    return directions[Random::get(0, static_cast<int>(directions.size()) - 1)];
}

bool MazeGenerator::isValidDirection(Position pos) {
    if (pos.x <= 0 || pos.y <= 0 || pos.x >= m_data.matrix[0].size() - 1 || pos.y >= m_data.matrix.size() - 1)
        return false;
    if (m_data.matrix[pos.y][pos.x] != Cell::wall)
        return false;

    return true;
}

void MazeGenerator::placeItems() {
    for (int i{ 0 }; i < m_settings.numItems; ++i) {
        int x = Random::get(1, m_settings.numCols - 2);
        int y = Random::get(1, m_settings.numRows - 2);
        m_data.matrix[y][x] = Cell::item;
    }
}

void MazeGenerator::carveAdditionalPassages() {
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };

    for (int x = 1; x < m_settings.numCols - 1; ++x) {
        // open a passage in the second-to-last row
        m_data.matrix[m_settings.numRows - 2][x] = Cell::passage;

        // choose a random position within safe bounds
        int randX = Random::get(2, m_settings.numCols - 3);
        int randY = Random::get(2, m_settings.numRows - 3);

        // choose a random direction (up, right, down, left)
        int dir = Random::get(0, 3);

        m_data.matrix[randY][randX] = Cell::passage;
        m_data.matrix[randY + dy[dir]][randX + dx[dir]] = Cell::passage;
    }
}