#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh {
public:
    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
    ~Mesh();

    void bind() const;
private:
    unsigned int vao, vbo, ebo;
};