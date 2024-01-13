#pragma once

#include <glm/vec3.hpp>
#include <vector>

#include "Direction.h"

namespace VoxelUtil {

    std::vector<glm::ivec3> getSurroundingGrid(glm::ivec3 center, Direction normal);
    glm::ivec3 getFaceOffset(Direction face);
    std::vector<float> getFaceVertices(int x, int y, int z, unsigned int textureIndex, Direction face, const std::vector<float>& vertexSkyLights, const std::vector<float>& vertexBlockLights);
}