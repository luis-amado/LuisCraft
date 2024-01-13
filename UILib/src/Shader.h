#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace UILib {

    class UIShader {
    public:
        UIShader() {};
        UIShader(const char* vertexFile, const char* fragmentFile);
        ~UIShader();

        void use() const;
        void destroy();

        void init(const char* vertexFile, const char* fragmentFile);

        void setUniform1i(const std::string& uniform, int value);
        void setUniform1f(const std::string& uniform, float value);
        void setUniform3f(const std::string& uniform, const glm::vec3& value);
        void setUniform4f(const std::string& uniform, const glm::vec4& value);
        void setUniformMatrix(const std::string& uniform, const glm::mat4& matrix);
    protected:
        unsigned int id;

    private:
        std::unordered_map<std::string, unsigned int> uniforms;

        enum class ShaderType {
            VERTEX, FRAGMENT, PROGRAM
        };

        std::string getSource(const char* file) const;
        void checkCompilation(unsigned int shader, ShaderType type) const;

        unsigned int getUniformLocation(const std::string& uniform);
    };

}