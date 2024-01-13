#pragma once

#include <vector>

enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    UP,
    DOWN
};

namespace DirectionUtil {
    const std::vector<Direction> all = {Direction::NORTH, Direction::SOUTH, Direction::EAST, Direction::WEST, Direction::UP, Direction::DOWN};
}