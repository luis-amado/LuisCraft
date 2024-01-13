#pragma once

#include "Font.h"

#include <vector>

namespace UILib {
namespace FontMesher {

    void generateTextMesh(const std::string& text, const Font& font, std::vector<float>& vertices);

    void addVertex(float x, float y, float texX, float texY, std::vector<float>& vertices);

}}