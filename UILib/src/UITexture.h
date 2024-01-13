#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

namespace UILib {

    class UITexture {
    public:
        UITexture()
            : id(0), width(0), height(0) {};
        UITexture(const char* filepath, unsigned int mipmapLevels = 4, GLuint filter = GL_NEAREST);
        UITexture(const unsigned char* bytes, unsigned int width, unsigned int height);
        ~UITexture();

        void bind(GLuint textureSlot = GL_TEXTURE0) const;
        void generate(const char* filepath, unsigned int mipmapLevels = 4, GLuint filter = GL_NEAREST);

        inline int getWidth() const { return width; }
        inline int getHeight() const { return height; }

    private:
        unsigned int id;
        int width, height;
    };

}