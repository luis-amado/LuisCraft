#include "ChunkSection.h"

#include <FastNoise/FastNoise.h>

#include "Chunk.h"
#include "VoxelUtil.h"

#include "../init/Blocks.h"

#define index(x, y, z) x + z * Chunk::CHUNK_WIDTH + y * Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH

ChunkSection::ChunkSection() : yPos(-1) {}

ChunkSection::~ChunkSection() {
    delete[] blocks;
}

void ChunkSection::updateLightLevelInSection(int x, int y, int z, LightType type, unsigned char level) {
    if (type == LightType::SKY) {
        skyLight.set(index(x, y, z), level);
    } else {
        blockLight.set(index(x, y, z), level);
    }
}

void ChunkSection::init(int _y, Chunk* _chunk) {

    yPos = _y;
    chunk = _chunk;

    blocks = new short[Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH];
    skyLight.init(Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH, 0);
    blockLight.init(Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH * Chunk::CHUNK_WIDTH, 0);

    generateTerrain();
}

void ChunkSection::generateTerrain() {

    int terrainHeight = 60, finalY;
    short block;

    auto simplexNoise = FastNoise::New<FastNoise::Simplex>();

    for (int x = 0; x < Chunk::CHUNK_WIDTH; x++) {
        for (int z = 0; z < Chunk::CHUNK_WIDTH; z++) {
            for (int y = 0; y < Chunk::CHUNK_WIDTH; y++) {

                finalY = yPos + y;

                // INITIAL PASS

                if (finalY > terrainHeight) {
                    block = Blocks::AIR.getBlockIndex();
                } else if (finalY == terrainHeight) {
                    block = Blocks::GRASS.getBlockIndex();
                } else if (finalY >= terrainHeight - 3) {
                    block = Blocks::DIRT.getBlockIndex();
                } else if (finalY > 0) {
                    block = Blocks::STONE.getBlockIndex();
                } else {
                    block = Blocks::DEEPSLATE_BRICKS.getBlockIndex();
                }

                int seed = 1;

                // CAVE PASS
                //if(block != Blocks::AIR.getBlockIndex()) {
                //    float scale = 30.0f;
                //    float noise = simplexNoise->GenSingle3D((x + chunk->coord.x * Chunk::CHUNK_WIDTH) / scale, (y + yPos) / scale, (z + chunk->coord.z * Chunk::CHUNK_WIDTH) / scale, seed);
                //    if (noise < -0.5f) {
                //        block = Blocks::AIR.getBlockIndex();
                //    }
                //}

                blocks[index(x, y, z)] = block;
                blockLight.set(index(x, y, z), Blocks::registry.blocks[block]->getLightLevel());
            }
        }
    }

}

short ChunkSection::getBlockInSection(int x, int y, int z) const {
    if (isInsideSection(x, y, z)) {
        return blocks[index(x,y,z)];
    } else {
        return chunk->getBlockLocal(x, y + yPos, z);
    }
}

short ChunkSection::getBlockInSection(glm::ivec3 pos) const {
    return getBlockInSection(pos.x, pos.y, pos.z);
}

bool ChunkSection::isInsideSection(int x, int y, int z) const {
    return x >= 0 && y >= 0 && z >= 0 && x < Chunk::CHUNK_WIDTH && y < Chunk::CHUNK_WIDTH && z < Chunk::CHUNK_WIDTH;
}

void ChunkSection::generateMesh() {

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    unsigned int vertexCount = 0;

    for (int x = 0; x < Chunk::CHUNK_WIDTH; x++) {
        for (int z = 0; z < Chunk::CHUNK_WIDTH; z++) {
            for (int y = 0; y < Chunk::CHUNK_WIDTH; y++) {

                const Block& block = *Blocks::registry.blocks[blocks[index(x,y,z)]];

                if(!block.isSolid()) continue;

                for (Direction face : DirectionUtil::all) {
                    glm::ivec3 offset = VoxelUtil::getFaceOffset(face);
                    if(getBlockInSection(x+offset.x, y+offset.y, z+offset.z)) continue;
                    addFace(x, y, z, block, face, vertices, indices, vertexCount);
                }

            }
        }
    }

    if(indices.size() > 0) {
        mesh.setMesh(vertices, indices);
    }

}

unsigned char ChunkSection::getLightLevelInSection(int x, int y, int z, LightType type) const {
    if (isInsideSection(x, y, z)) {
        if (type == LightType::SKY) {
            return skyLight.get(index(x, y, z));
        } else {
            return blockLight.get(index(x, y, z));
        }
    } else {
        return chunk->getLightLevelLocal(x, yPos + y, z, type);
    }
}

void ChunkSection::addFace(int x, int y, int z, const Block& block, Direction face, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& vertexCount) {

    // 4 light levels, one for each vertex
    // we need the 3x3 grid of light levels surrounding this face

    std::vector<float> vertexSkyLights(4), vertexBlockLights(4);


    if (block.getLightLevel() > 0) {
        glm::ivec3 faceOffset = VoxelUtil::getFaceOffset(face);
        vertexSkyLights[0] = vertexSkyLights[1] = vertexSkyLights[2] = vertexSkyLights[3] = getLightLevelInSection(x + faceOffset.x, y + faceOffset.y, z + faceOffset.z, LightType::SKY) / 15.0f;
        vertexBlockLights[0] = vertexBlockLights[1] = vertexBlockLights[2] = vertexBlockLights[3] = getLightLevelInSection(x + faceOffset.x, y + faceOffset.y, z + faceOffset.z, LightType::BLOCK) / 15.0f;
    } else {
        calculateSmoothLightVertices(x, y, z, face, vertexSkyLights, LightType::SKY);
        calculateSmoothLightVertices(x, y, z, face, vertexBlockLights, LightType::BLOCK);
    }

    std::vector<float> faceVertices = VoxelUtil::getFaceVertices(x, y, z, block.getTextures().getFace(face), face, vertexSkyLights, vertexBlockLights);
    vertices.insert(vertices.end(), faceVertices.begin(), faceVertices.end());

    unsigned int newIndices[] = {
        vertexCount,
        vertexCount+1,
        vertexCount+2,
        vertexCount+2,
        vertexCount+3,
        vertexCount
    };

    indices.insert(indices.end(), std::begin(newIndices), std::end(newIndices));
    vertexCount += 4;
}

void ChunkSection::calculateSmoothLightVertices(int x, int y, int z, Direction face, std::vector<float>& vertexLights, LightType lightType) const {

    std::vector<float> lightGrid = getSurroundingLightLevels(x, y, z, face, lightType);
    vertexLights[0] = average4(lightGrid[0], lightGrid[1], lightGrid[3], lightGrid[4]);
    vertexLights[1] = average4(lightGrid[3], lightGrid[4], lightGrid[6], lightGrid[7]);
    vertexLights[2] = average4(lightGrid[4], lightGrid[5], lightGrid[7], lightGrid[8]);
    vertexLights[3] = average4(lightGrid[1], lightGrid[2], lightGrid[4], lightGrid[5]);

}

std::vector<float> ChunkSection::getSurroundingLightLevels(int x, int y, int z, Direction face, LightType type) const {

    std::vector<float> lightGrid(9, 0.0f);
    glm::ivec3 center = glm::ivec3(x, y, z) + VoxelUtil::getFaceOffset(face);

    std::vector<glm::ivec3> positionGrid = VoxelUtil::getSurroundingGrid(center, face);
    
    // the corners can be occluded
    // TODO: this will not work when there are different block shapes
    
    // 0 1 2
    // 3 4 5
    // 6 7 8

    // corner 0
    if (!Blocks::registry.blocks[getBlockInSection(positionGrid[1])]->isSolid() || !Blocks::registry.blocks[getBlockInSection(positionGrid[3])]->isSolid()) {
        lightGrid[0] = getLightLevelInSection(positionGrid[0].x, positionGrid[0].y, positionGrid[0].z, type) / 15.0f;
    }

    lightGrid[1] = getLightLevelInSection(positionGrid[1].x, positionGrid[1].y, positionGrid[1].z, type) / 15.0f;

    // corner 2
    if (!Blocks::registry.blocks[getBlockInSection(positionGrid[1])]->isSolid() || !Blocks::registry.blocks[getBlockInSection(positionGrid[5])]->isSolid()) {
        lightGrid[2] = getLightLevelInSection(positionGrid[2].x, positionGrid[2].y, positionGrid[2].z, type) / 15.0f;
    }

    lightGrid[3] = getLightLevelInSection(positionGrid[3].x, positionGrid[3].y, positionGrid[3].z, type) / 15.0f;
    lightGrid[4] = getLightLevelInSection(positionGrid[4].x, positionGrid[4].y, positionGrid[4].z, type) / 15.0f;
    lightGrid[5] = getLightLevelInSection(positionGrid[5].x, positionGrid[5].y, positionGrid[5].z, type) / 15.0f;

    // corner 6
    if (!Blocks::registry.blocks[getBlockInSection(positionGrid[3])]->isSolid() || !Blocks::registry.blocks[getBlockInSection(positionGrid[7])]->isSolid()) {
        lightGrid[6] = getLightLevelInSection(positionGrid[6].x, positionGrid[6].y, positionGrid[6].z, type) / 15.0f;
    }

    lightGrid[7] = getLightLevelInSection(positionGrid[7].x, positionGrid[7].y, positionGrid[7].z, type) / 15.0f;

    // corner 8
    if (!Blocks::registry.blocks[getBlockInSection(positionGrid[5])]->isSolid() || !Blocks::registry.blocks[getBlockInSection(positionGrid[7])]->isSolid()) {
        lightGrid[8] = getLightLevelInSection(positionGrid[8].x, positionGrid[8].y, positionGrid[8].z, type) / 15.0f;
    }

    return lightGrid;

}

float ChunkSection::average4(float a, float b, float c, float d) const {
    return (a + b + c + d) / 4.0f;
}