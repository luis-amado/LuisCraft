#pragma once

#include <glm/glm.hpp>
#include <string>

#include "font/Font.h"
#include "font/FontMesher.h"
#include "../../../Shader.h"

namespace UILib {

    class Text {

    public:
        Text(const std::string& text, Font& font);
        ~Text();

        Text(const Text& t) = delete;

        void setText(const std::string& newText);
        void setFont(Font& font);

        static void init();
        static void destroy();
        
        void bind() const;
        void render() const;

        inline std::string getText() const { return text; }
        inline Font& getFont() const { return *font; }

        inline static UIShader& getTextShader() { return textShader; }

    private:
        unsigned int vao, vbo;
        unsigned int vertexCount = 0;
        std::string text;
        Font* font;

        static UIShader textShader;

        void generateMesh();

    };

}