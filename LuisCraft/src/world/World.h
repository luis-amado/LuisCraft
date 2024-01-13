#pragma once

#include <unordered_map>

#include "Chunk.h"
#include "ChunkCoord.h"

class World {

public:
    static const int RADIUS_IN_CHUNKS;
    static const int DIAMETER_IN_CHUNKS;

    World();
    ~World();

    short getBlockGlobal(int x, int y, int z);
    bool isInsideWorld(int x, int y, int z);

    unsigned char getLightLevelGlobal(int x, int y, int z, LightType type);
    void updateLightLevelGlobal(int x, int y, int z, LightType type, unsigned char lightLevel);

    ChunkCoord getChunkCoord(int x, int z);
    Chunk* getChunkAt(int x, int z);

    std::unordered_map<ChunkCoord, Chunk*> chunks;
private:
    
};