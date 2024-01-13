#include "Chunk.h"
#include "World.h"

#include <iostream>
#include <queue>
#include <glm/glm.hpp>

#include "VoxelUtil.h"

#include "../init/Blocks.h"

const int Chunk::CHUNK_WIDTH = 16;
const int Chunk::CHUNK_HEIGHT_IN_SECTIONS = 16;
const int Chunk::CHUNK_HEIGHT = CHUNK_HEIGHT_IN_SECTIONS * CHUNK_WIDTH;

Chunk::Chunk(int x, int z, World& _world) :
    coord(x,z), world(_world) {

    sections = new ChunkSection[CHUNK_HEIGHT_IN_SECTIONS];

    for (int i = 0; i < CHUNK_HEIGHT_IN_SECTIONS; i++) {
        sections[i].init(i * CHUNK_WIDTH, this);
    }

    // sky light continues downward until it hits a block
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {

            for (int y = CHUNK_HEIGHT - 1; y >= 0; y--) {
                if (Blocks::registry.blocks[sections[getSection(y)].getBlockInSection(x, y % CHUNK_WIDTH, z)]->isSolid())
                    break;
                sections[getSection(y)].updateLightLevelInSection(x, y % CHUNK_WIDTH, z, LightType::SKY, 15);
            }

        }
    }
}

void Chunk::propagateLighting() {
    //propagate lighting, usign a bfs algorithm
    for (int y = CHUNK_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {

                propagateLightDFS(x, y, z, LightType::SKY, getLightLevelLocal(x, y, z, LightType::SKY));
                propagateLightDFS(x, y, z, LightType::BLOCK, getLightLevelLocal(x, y, z, LightType::BLOCK));

            }
        }
    }
}

// I'm not sure why this recursive approach is way faster but it is also easier to understand so it's just better!
// My guess is that on average, the call stack overhead is less than the queue overhead
void Chunk::propagateLightDFS(int x, int y, int z, LightType type, unsigned char lightLevel) {

    if(lightLevel <= 1 || lightLevel > 15) return;

    glm::ivec3 nextPos;
    glm::ivec3 currPos = {x, y, z};

    for (Direction dir : DirectionUtil::all) {
        nextPos = currPos + VoxelUtil::getFaceOffset(dir);
        unsigned char lightLevelAtNextPos = getLightLevelLocal(nextPos.x, nextPos.y, nextPos.z, type);
        if (lightLevelAtNextPos < lightLevel - 1 && !Blocks::registry.blocks[getBlockLocal(nextPos.x, nextPos.y, nextPos.z)]->isSolid()) {
            updateLightLevelLocal(nextPos.x, nextPos.y, nextPos.z, type, lightLevel -1);
            propagateLightDFS(nextPos.x, nextPos.y, nextPos.z, type, lightLevel - 1);
        }
    }

}

// was more interesting to figure out, but harder logic and also significantly slower :(
//void Chunk::propagateLightBFS(int x, int y, int z) {
//
//    char lightLevel = getLightLevelLocal(x, y, z);
//    if(lightLevel <= 1) return;
//    lightLevel--;
//
//    std::queue<glm::ivec3> q;
//    q.push({x, y, z});
//
//    int i, currSize;
//    glm::ivec3 currPos;
//    glm::ivec3 nextPos;
//    while (!q.empty() && lightLevel > 0) {
//
//        currSize = q.size();
//        for (i = 0; i < currSize; i++) {
//
//            currPos = q.front();
//            q.pop();
//
//            // add neighbors to the queue
//            for (Direction dir : DirectionUtil::all) {
//                nextPos = currPos + VoxelUtil::getFaceOffset(dir);
//                unsigned char lightLevelAtNextPos = getLightLevelLocal(nextPos.x, nextPos.y, nextPos.z);
//                if (lightLevelAtNextPos < lightLevel && !Blocks::registry.blocks[getBlockLocal(nextPos.x, nextPos.y, nextPos.z)]->isSolid()) {
//                    updateLightLevelLocal(nextPos.x, nextPos.y, nextPos.z, lightLevel);
//                    q.push(nextPos);
//                }
//            }
//
//
//        }
//        lightLevel--;
//
//    }
//
//}

Chunk::~Chunk() {
    delete[] sections;
}

void Chunk::generateMesh() {
    for (int i = 0; i < CHUNK_HEIGHT_IN_SECTIONS; i++) {
        sections[i].generateMesh();
    }
}

short Chunk::getBlockLocal(int x, int y, int z) {
    if (isInsideChunk(x, y, z)) {
        return sections[getSection(y)].getBlockInSection(x, y % CHUNK_WIDTH, z);
    } else {
        return world.getBlockGlobal(x + coord.x * CHUNK_WIDTH, y, z + coord.z * CHUNK_WIDTH);
    }
}

unsigned char Chunk::getLightLevelLocal(int x, int y, int z, LightType type) {
    if (isInsideChunk(x, y, z)) {
        return sections[getSection(y)].getLightLevelInSection(x, y % CHUNK_WIDTH, z, type);
    } else {
        return world.getLightLevelGlobal(x + coord.x * CHUNK_WIDTH, y, z + coord.z * CHUNK_WIDTH, type);
    }
}

void Chunk::updateLightLevelLocal(int x, int y, int z, LightType type, unsigned char lightLevel) {
    if (isInsideChunk(x, y, z)) {
        sections[getSection(y)].updateLightLevelInSection(x, y % CHUNK_WIDTH, z, type, lightLevel);
    } else {
        world.updateLightLevelGlobal(x + coord.x * CHUNK_WIDTH, y, z + coord.z * CHUNK_WIDTH, type, lightLevel);
    }
}

bool Chunk::isInsideChunk(int x, int y, int z) {
    return x >= 0 && y >= 0 && z >= 0 && x < CHUNK_WIDTH && y < CHUNK_HEIGHT_IN_SECTIONS * CHUNK_WIDTH && z < CHUNK_WIDTH;
}

int Chunk::getSection(int y) {
    return y / CHUNK_WIDTH;
}