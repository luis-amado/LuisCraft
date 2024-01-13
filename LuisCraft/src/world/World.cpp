#include "World.h"

#include <iostream>
#include <chrono>
#include <string>

#include "../init/Blocks.h"

const int World::RADIUS_IN_CHUNKS = 2;

void printDuration(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point stop, std::string action) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Completed " << action << " in " << duration.count() / (float)1e6 << " s\n";
}

World::World() {

    auto start = std::chrono::high_resolution_clock::now();
    for (int x = -RADIUS_IN_CHUNKS; x <= RADIUS_IN_CHUNKS; x++) {
        for (int z = -RADIUS_IN_CHUNKS; z <= RADIUS_IN_CHUNKS; z++) {
            chunks[{x,z}] = new Chunk(x, z, *this);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    printDuration(start, stop, "Generate Chunks");
    
    start = std::chrono::high_resolution_clock::now();
    for (auto& [coord, chunk] : chunks) {
        chunk->propagateLighting();
    }
    stop = std::chrono::high_resolution_clock::now();
    printDuration(start, stop, "Propagate Lights");

    start = std::chrono::high_resolution_clock::now();
    for (auto& [coord, chunk] : chunks) {
        chunk->generateMesh();
    }
    stop = std::chrono::high_resolution_clock::now();
    printDuration(start, stop, "Generate Meshes");

}

World::~World() {
    for (auto& [coord, chunk] : chunks) {
        delete chunk;
    }
}

short World::getBlockGlobal(int x, int y, int z) {
    if (isInsideWorld(x, y, z)) {
        ChunkCoord coord = getChunkCoord(x, z);
        int localX = x - coord.x * Chunk::CHUNK_WIDTH;
        int localZ = z - coord.z * Chunk::CHUNK_WIDTH;
        return chunks[coord]->getBlockLocal(localX, y, localZ);
    } else {
        return Blocks::AIR.getBlockIndex();
    }
}

unsigned char World::getLightLevelGlobal(int x, int y, int z, LightType type) {
    if (isInsideWorld(x, y, z)) {
        ChunkCoord coord = getChunkCoord(x, z);
        int localX = x - coord.x * Chunk::CHUNK_WIDTH;
        int localZ = z - coord.z * Chunk::CHUNK_WIDTH;
        return chunks[coord]->getLightLevelLocal(localX, y, localZ, type);
    } else {
        return 15;
    }
}

void World::updateLightLevelGlobal(int x, int y, int z, LightType type, unsigned char lightLevel) {
#ifdef _DEBUG
    if (isInsideWorld(x, y, z)) {
#endif
        ChunkCoord coord = getChunkCoord(x, z);
        int localX = x - coord.x * Chunk::CHUNK_WIDTH;
        int localZ = z - coord.z * Chunk::CHUNK_WIDTH;
        chunks[coord]->updateLightLevelLocal(localX, y, localZ, type, lightLevel);
#ifdef _DEBUG
    } else {
        std::cout << "Updated light out of the world." << std::endl;
    }
#endif
}

bool World::isInsideWorld(int x, int y, int z) {
    if(y < 0 || y >= Chunk::CHUNK_HEIGHT_IN_SECTIONS * Chunk::CHUNK_WIDTH) return false;
    ChunkCoord coord = getChunkCoord(x, z);
    bool found = chunks.find(coord) != chunks.end();
    return found;
}

Chunk* World::getChunkAt(int x, int z) {
     ChunkCoord coord = getChunkCoord(x, z);
     return chunks[coord];
}

ChunkCoord World::getChunkCoord(int x, int z) {
    int chunkX = x;
    int chunkZ = z;
    if(x < 0) chunkX -= 15;
    if(z < 0) chunkZ -= 15;
    return {chunkX / Chunk::CHUNK_WIDTH, chunkZ / Chunk::CHUNK_WIDTH};
}