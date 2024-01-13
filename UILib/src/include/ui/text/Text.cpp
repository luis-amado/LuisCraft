#include "Text.h"

namespace UILib {

    UIShader Text::textShader;

    void Text::init() {
        textShader.init("res/shaders/text.vs", "res/shaders/text.fs");
    }

    void Text::destroy() {
        textShader.destroy();
    }

    Text::Text(const std::string& _text, Font& _font)
        : text(_text), font(&_font) {

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        generateMesh();
    }

    Text::~Text() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }

    void Text::setText(const std::string& _text) {
        text = _text;
        generateMesh();
    }
    
    void Text::setFont(Font& _font) {
        font = &_font;
        generateMesh();
    }

    void Text::generateMesh() {

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        std::vector<float> vertices;
        FontMesher::generateTextMesh(text, *font, vertices);

        vertexCount = vertices.size() / 4;

        glBufferData(GL_ARRAY_BUFFER, 4 * vertexCount * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

    }

    void Text::bind() const {
        glBindVertexArray(vao);
        font->use();
    }

    void Text::render() const {

        bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexCount);

    }

}