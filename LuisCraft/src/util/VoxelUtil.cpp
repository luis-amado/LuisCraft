#include "VoxelUtil.h"

namespace VoxelUtil {

    std::vector<glm::ivec3> getSurroundingGrid(glm::ivec3 center, Direction normal) {

        switch (normal) {
            default:
            case Direction::NORTH:
                return {
                    {center.x+1, center.y+1, center.z},
                    {center.x+0, center.y+1, center.z},
                    {center.x-1, center.y+1, center.z},
                    {center.x+1, center.y+0, center.z},
                    {center.x+0, center.y+0, center.z},
                    {center.x-1, center.y+0, center.z},
                    {center.x+1, center.y-1, center.z},
                    {center.x+0, center.y-1, center.z},
                    {center.x-1, center.y-1, center.z}
                };
            case Direction::SOUTH:
                return {
                    {center.x-1, center.y+1, center.z},
                    {center.x+0, center.y+1, center.z},
                    {center.x+1, center.y+1, center.z},
                    {center.x-1, center.y+0, center.z},
                    {center.x+0, center.y+0, center.z},
                    {center.x+1, center.y+0, center.z},
                    {center.x-1, center.y-1, center.z},
                    {center.x+0, center.y-1, center.z},
                    {center.x+1, center.y-1, center.z}
                };
            case Direction::EAST:
                return {
                    {center.x, center.y+1, center.z+1},
                    {center.x, center.y+1, center.z+0},
                    {center.x, center.y+1, center.z-1},
                    {center.x, center.y+0, center.z+1},
                    {center.x, center.y+0, center.z+0},
                    {center.x, center.y+0, center.z-1},
                    {center.x, center.y-1, center.z+1},
                    {center.x, center.y-1, center.z+0},
                    {center.x, center.y-1, center.z-1}
                };
            case Direction::WEST:
                return {
                    {center.x, center.y+1, center.z-1},
                    {center.x, center.y+1, center.z+0},
                    {center.x, center.y+1, center.z+1},
                    {center.x, center.y+0, center.z-1},
                    {center.x, center.y+0, center.z+0},
                    {center.x, center.y+0, center.z+1},
                    {center.x, center.y-1, center.z-1},
                    {center.x, center.y-1, center.z+0},
                    {center.x, center.y-1, center.z+1}
                };
            case Direction::UP:
                return {
                    {center.x-1, center.y, center.z-1},
                    {center.x+0, center.y, center.z-1},
                    {center.x+1, center.y, center.z-1},
                    {center.x-1, center.y, center.z+0},
                    {center.x+0, center.y, center.z+0},
                    {center.x+1, center.y, center.z+0},
                    {center.x-1, center.y, center.z+1},
                    {center.x+0, center.y, center.z+1},
                    {center.x+1, center.y, center.z+1}
                };
            case Direction::DOWN:
                return {
                    {center.x+1, center.y, center.z-1},
                    {center.x+0, center.y, center.z-1},
                    {center.x-1, center.y, center.z-1},
                    {center.x+1, center.y, center.z+0},
                    {center.x+0, center.y, center.z+0},
                    {center.x-1, center.y, center.z+0},
                    {center.x+1, center.y, center.z+1},
                    {center.x+0, center.y, center.z+1},
                    {center.x-1, center.y, center.z+1}
                };
        }

    }

    glm::ivec3 getFaceOffset(Direction face) {
        switch (face) {

            case Direction::NORTH:
                return {0, 0, -1};
            case Direction::SOUTH:
                return {0, 0, 1};
            case Direction::EAST:
                return {1, 0, 0};
            case Direction::WEST:
                return {-1, 0, 0};
            case Direction::UP:
                return {0, 1, 0};
            case Direction::DOWN:
                return {0, -1, 0};

        }
    }

    std::vector<float> getFaceVertices(int x, int y, int z, unsigned int textureIndex, Direction face, const std::vector<float>& vertexSkyLights, const std::vector<float>& vertexBlockLights) {

        float textureGrid = 1.0f / 4.0f;

        unsigned int row = textureIndex / 4;
        unsigned int col = textureIndex % 4;

        float texXMin = textureGrid * col;
        float texYMin = 1.0f - (row + 1.0f) * textureGrid;
        float texXMax = texXMin + textureGrid;
        float texYMax = texYMin + textureGrid;

        switch (face) {
            case Direction::NORTH:
                return {
                    x+1.0f, y+1.0f, z+0.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+1.0f, y+0.0f, z+0.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+0.0f, y+0.0f, z+0.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+0.0f, y+1.0f, z+0.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
            case Direction::SOUTH:
                return {
                    x+0.0f, y+1.0f, z+1.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+0.0f, y+0.0f, z+1.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+1.0f, y+0.0f, z+1.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+1.0f, y+1.0f, z+1.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
            case Direction::EAST:
                return {
                    x+1.0f, y+1.0f, z+1.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+1.0f, y+0.0f, z+1.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+1.0f, y+0.0f, z+0.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+1.0f, y+1.0f, z+0.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
            case Direction::WEST:
                return {
                    x+0.0f, y+1.0f, z+0.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+0.0f, y+0.0f, z+0.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+0.0f, y+0.0f, z+1.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+0.0f, y+1.0f, z+1.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
            case Direction::UP:
                return {
                    x+0.0f, y+1.0f, z+0.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+0.0f, y+1.0f, z+1.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+1.0f, y+1.0f, z+1.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+1.0f, y+1.0f, z+0.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
            case Direction::DOWN:
                return {
                    x+1.0f, y+0.0f, z+0.0f,  texXMin, texYMax, vertexSkyLights[0], vertexBlockLights[0],
                    x+1.0f, y+0.0f, z+1.0f,  texXMin, texYMin, vertexSkyLights[1], vertexBlockLights[1],
                    x+0.0f, y+0.0f, z+1.0f,  texXMax, texYMin, vertexSkyLights[2], vertexBlockLights[2],
                    x+0.0f, y+0.0f, z+0.0f,  texXMax, texYMax, vertexSkyLights[3], vertexBlockLights[3]
                };
        }
    }

}