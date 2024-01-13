#pragma once

#include "../UIBlock.h"
#include "Text.h"

#include <vector>
#include <sstream>
#include <glm/glm.hpp>

namespace UILib {

    class TextBox : public UIBlock {

    public:
        TextBox(std::string _text, Font& _font, glm::vec4 _fillColor);

        void onBoxUpdated() override;
        void renderAdditional(UIShader& shader, const glm::mat4& projection, const UIBlock& parent) override;

        void setText(std::string _text);
        inline std::string getText() const { return text; }

        TextBox& setFont(Font& _font);
        TextBox& setFontSize(int _fontSize);
        TextBox& setLineHeight(int _lineHeight);
        TextBox& setTextColor(glm::vec4 _textColor);

    private:
        std::string text;
        std::vector<Text*> textLines;

        Font* font;
        int fontSize = 12;
        int lineHeight = -1;
        glm::vec4 textColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    };


}