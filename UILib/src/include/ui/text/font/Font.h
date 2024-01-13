#pragma once

#include <string>
#include <unordered_map>

#include "../../../../UITexture.h"

namespace UILib {

    struct Character {
        char id;
        int width, height, x, y, xadvance, xoffset, yoffset;
    };

    class Font {

    public:

        Font(const std::string& filepath);
        
        const Character& getChar(char character) const;
        inline int getBase() const { return base; }
        inline int getSize() const { return size; }
        inline int getLineHeight() const { return lineHeight; }
        inline const UITexture& getTexture() const { return texture; }

        void use() const;

    private:
        std::unordered_map<char, Character> characters;
        int base, size, lineHeight;

        UITexture texture;

    };

}