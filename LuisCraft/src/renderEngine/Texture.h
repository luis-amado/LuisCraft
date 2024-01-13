#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture {
public:
    Texture() 
        : id(0), width(0), height(0) {};
    Texture(const char* filepath, unsigned int mipmapLevels = 4, GLuint filter = GL_NEAREST);
    Texture(const unsigned char* bytes, unsigned int width, unsigned int height);
    ~Texture();

    void bind(GLuint textureSlot = GL_TEXTURE0) const;
    void generate(const char* filepath, unsigned int mipmapLevels = 4, GLuint filter = GL_NEAREST);
    
    inline int getWidth() const { return width; }
    inline int getHeigth() const { return height; }

private:
    unsigned int id;
    int width, height;
};