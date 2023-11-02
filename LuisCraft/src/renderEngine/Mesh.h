#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh {
public:
    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
    ~Mesh();

    void bind() const;

    inline unsigned int indexCount() const { return count; }
private:
    unsigned int vao, vbo, ebo;
    unsigned int count;
};