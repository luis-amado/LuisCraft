#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../renderEngine/Mesh.h"
#include "Direction.h"
#include "NibbleArray.h"
#include "../block/Block.h"

class Chunk;

enum class LightType {
    SKY, BLOCK
};

class ChunkSection {

public:
    ChunkSection();
    ~ChunkSection();

    void init(int _y, Chunk* _chunk);
    short getBlockInSection(int x, int y, int z) const;
    short getBlockInSection(glm::ivec3 pos) const;
    void generateMesh();

    unsigned char getLightLevelInSection(int x, int y, int z, LightType type) const;
    void updateLightLevelInSection(int x, int y, int z, LightType type, unsigned char level);

    Mesh mesh;
    int yPos;
private:

    Chunk* chunk;
    short* blocks;
    NibbleArray skyLight, blockLight;

    void generateTerrain();

    bool isInsideSection(int x, int y, int z) const;

    void addFace(int x, int y, int z, const Block& block, Direction face, std::vector<float>& vertices, std::vector<unsigned int>& indices, unsigned int& vertexCount);
    std::vector<float> getSurroundingLightLevels(int x, int y, int z, Direction face, LightType type) const;

    void calculateSmoothLightVertices(int x, int y, int z, Direction face, std::vector<float>& vertexLights, LightType lightType) const;

    float average4(float a, float b, float c, float d) const;

};