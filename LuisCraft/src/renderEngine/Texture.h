#pragma once

#include <glad/glad.h>
#include <stb_image.h>

class Texture {
public:
    Texture(const char* filepath, unsigned int mipmapLevels = 4, GLuint filter = GL_NEAREST);
    ~Texture();

    void bind() const;
    
    inline int getWidth() const { return width; }
    inline int getHeigth() const { return height; }

private:
    unsigned int id;
    int width, height;
};