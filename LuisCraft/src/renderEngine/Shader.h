#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>

class Shader {
public:
    Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

    void use() const;

    void setUniform(std::string uniform, float value);
    void setUniform(std::string uniform, glm::vec3 value);
protected:
    unsigned int id;

private:
    std::unordered_map<std::string, unsigned int> uniforms;

    enum class ShaderType {
        VERTEX, FRAGMENT, PROGRAM
    };

    std::string getSource(const char* file) const;
    void checkCompilation(unsigned int shader, ShaderType type) const;

    unsigned int getUniformLocation(std::string uniform);
};