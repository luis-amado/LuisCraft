#pragma once

#include <algorithm>

struct ChunkCoord {

    int x, z;

    ChunkCoord(int _x, int _z) : x(_x), z(_z) {}

    bool operator==(const ChunkCoord& other) const {
        return x == other.x && z == other.z;
    }

};

template <>
struct std::hash<ChunkCoord> {
    std::size_t operator()(const ChunkCoord& k) const {
        return (std::hash<int>()(k.x)
                ^ (std::hash<int>()(k.z) << 1) >> 1);
    }
};