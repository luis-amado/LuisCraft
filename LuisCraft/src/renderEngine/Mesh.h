#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh {
public:
    Mesh();
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~Mesh();

    void bind() const;
    void setMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    inline unsigned int indexCount() const { return count; }
private:
    unsigned int vao, vbo, ebo;
    unsigned int count;
};