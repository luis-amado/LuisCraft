#include "Shader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile) {

    std::string vertexSrc = getSource(vertexFile);
    std::string fragmentSrc = getSource(fragmentFile);

    const char* vertexSource = vertexSrc.c_str();
    const char* fragmentSource = fragmentSrc.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    checkCompilation(vertex, ShaderType::VERTEX);

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    checkCompilation(fragment, ShaderType::FRAGMENT);

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompilation(id, ShaderType::PROGRAM);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() const {
    glUseProgram(id);
}

void Shader::setUniform(std::string uniform, float value) {
    glUniform1f(getUniformLocation(uniform), value);
}

void Shader::setUniform(std::string uniform, glm::vec3 value) {
    glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
}

std::string Shader::getSource(const char* file) const {
    std::ifstream istream;
    istream.open(file);
    if (!istream.is_open()) {
        std::cout << "Error opening file: " + std::string(file) << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << istream.rdbuf();
    istream.close();

    return ss.str();
}

void Shader::checkCompilation(unsigned int shader, ShaderType type) const {

    int success;
    char infoLog[512];

    if (type != ShaderType::PROGRAM) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Error compiling " << (type == ShaderType::VERTEX ? "vertex" : "fragment") << " shader:\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Error linking shader program:\n" << infoLog << std::endl;
        }
    }

}

unsigned int Shader::getUniformLocation(std::string uniform) {

    if (uniforms.find(uniform) == uniforms.end()) {
        unsigned int location = glGetUniformLocation(id, uniform.c_str());
        uniforms.insert({uniform, location});
        return location;
    } else {
        return uniforms.at(uniform);
    }

}