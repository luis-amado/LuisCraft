#include "UITexture.h"

namespace UILib {

    UITexture::UITexture(const char* filepath, unsigned int mipmapLevels, GLuint filter)
        : id(0) {
        generate(filepath, mipmapLevels, filter);
    }

    UITexture::UITexture(const unsigned char* bytes, unsigned int width, unsigned int height) {

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    }

    void UITexture::generate(const char* filepath, unsigned int mipmapLevels, GLuint filter) {

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(filepath, &width, &height, nullptr, 4);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmapLevels);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);

    }

    UITexture::~UITexture() {
        glDeleteTextures(1, &id);
    }

    void UITexture::bind(GLuint textureSlot) const {
        glActiveTexture(textureSlot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

}