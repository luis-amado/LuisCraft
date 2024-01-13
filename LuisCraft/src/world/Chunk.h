#pragma once

#include "ChunkSection.h"
#include "ChunkCoord.h"

class World;

class Chunk {

public:

    Chunk(int x, int z, World& world);
    ~Chunk();

    ChunkCoord coord;

    static const int CHUNK_WIDTH;
    static const int CHUNK_HEIGHT_IN_SECTIONS;
    static const int CHUNK_HEIGHT;
    ChunkSection* sections;

    short getBlockLocal(int x, int y, int z);
    bool isInsideChunk(int x, int y, int z);

    unsigned char getLightLevelLocal(int x, int y, int z, LightType type);
    void updateLightLevelLocal(int x, int y, int z, LightType type, unsigned char lightLevel);

    int getSection(int y);

    void propagateLighting();
    void generateMesh();

private:

    void propagateLightDFS(int x, int y, int z, LightType type, unsigned char lightLevel);
    // void propagateLightBFS(int x, int y, int z); // unused

    World& world;
};