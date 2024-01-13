#pragma once

#include "Direction.h"

struct BlockTextures {
    unsigned int north, south, east, west, up, down; // north, south, east, west, up, down

    unsigned int getFace(Direction face) const {
        switch (face) {
            case Direction::NORTH: return north;
            case Direction::SOUTH: return south;
            case Direction::EAST: return east;
            case Direction::WEST: return west;
            case Direction::UP: return up;
            case Direction::DOWN: return down;
        }
        return north;
    }

    static BlockTextures all(unsigned int tex) {
        return {tex, tex, tex, tex, tex, tex};
    }

    static BlockTextures sideUpDown(unsigned int side, unsigned int up, unsigned int down) {
        return {side, side, side, side, up, down};
    }

    static BlockTextures sideEnd(unsigned int side, unsigned int end) {
        return {side, side, side, side, end, end};
    }

    static BlockTextures nsewup(unsigned int north, unsigned int south, unsigned int east, unsigned int west, unsigned int up, unsigned int down) {
        return {north, south, east, west, up, down};
    }
};