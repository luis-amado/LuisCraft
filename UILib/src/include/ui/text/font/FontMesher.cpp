#include "FontMesher.h"

namespace UILib {
namespace FontMesher {

    void generateTextMesh(const std::string& text, const Font& font, std::vector<float>& vertices) {

        // generate a quad (triangle_strip) per character on the text, with the origin on the bottom left

        int texH = font.getTexture().getHeight();
        int texW = font.getTexture().getWidth();

        int bottomUV;
        int yoff;
        int cursorPos = 0;
        for (char c : text) {
            const Character& character = font.getChar(c);

            bottomUV = texH - character.y - character.height;
            yoff = font.getBase() - character.yoffset - character.height;

            // vertices in order: bottom left, bottom right, top left, top right
            // TODO: missing offsets
            addVertex(character.xoffset + cursorPos, yoff, (float)character.x / texW, (float)bottomUV / texH, vertices);
            addVertex(character.xoffset + cursorPos + character.width, yoff, (float)(character.x + character.width) / texW, (float)bottomUV / texH, vertices);
            addVertex(character.xoffset + cursorPos, yoff + character.height, (float)character.x / texW, (float)(bottomUV + character.height) / texH, vertices);
            addVertex(character.xoffset + cursorPos + character.width, yoff + character.height, (float)(character.x + character.width) / texW, (float)(bottomUV + character.height) / texH, vertices);

            cursorPos += character.xadvance;

        }

    }

    void addVertex(float x, float y, float texX, float texY, std::vector<float>& vertices) {
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(texX);
        vertices.push_back(texY);
    }

}}