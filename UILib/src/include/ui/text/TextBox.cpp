#include "TextBox.h"

namespace UILib {

    TextBox::TextBox(std::string _text, Font& _font, glm::vec4 _fillColor)
        : UIBlock(_fillColor), text(_text), font(&_font) {}

    void TextBox::setText(std::string _text) {
        text = _text;
        onBoxUpdated();
    }

    void TextBox::onBoxUpdated() {

        for (Text* line : textLines) {
            delete line;
        }
        textLines.clear();

        // we know the size of the box now, we need to calculate the new lines

        float currentLineWidth = 0;
        std::stringstream line;
        std::string remainingText = text;
        while (remainingText.length() > 0) {
            currentLineWidth += font->getChar(remainingText[0]).xadvance * (float) fontSize / font->getSize();
            while (currentLineWidth <= width) {
                line << remainingText[0];
                remainingText.erase(0, 1);
                if (remainingText.length() == 0) break;
                currentLineWidth += font->getChar(remainingText[0]).xadvance * (float)fontSize / font->getSize();
            }

            if (line.str().size() == 0) {
                std::cout << "Can't fit text on box" << std::endl;
                break;
            }

            Text* textLine = new Text(line.str(), *font);
            textLines.push_back(textLine);

            currentLineWidth = 0;
            line.str("");

        }

    }

    void TextBox::renderAdditional(UIShader& shader, const glm::mat4& projection, const UIBlock& parent) {
        UIShader& textShader = Text::getTextShader();
        textShader.use();
        textShader.setUniformMatrix("projection", projection);
        textShader.setUniform4f("textColor", textColor);

        glm::mat4 model(1.0f);
        float scale = (float)fontSize / font->getSize();

        float actualLineHeight = font->getLineHeight() * scale;

        for (int i = 0; i < textLines.size(); i++) {
            model = glm::identity<glm::mat4>();
            model = glm::translate(model, glm::vec3(x, y + height - actualLineHeight * (i+1), 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, 1.0f));
            textShader.setUniformMatrix("model", model);
            textLines[i]->render();
        }

        shader.use();
    }

    TextBox& TextBox::setFont(Font& _font) {
        font = &_font;
        return *this;
    }

    TextBox& TextBox::setFontSize(int _fontSize) {
        fontSize = _fontSize;
        return *this;
    }

    TextBox& TextBox::setLineHeight(int _lineHeight) {
        lineHeight = _lineHeight;
        return *this;
    }

    TextBox& TextBox::setTextColor(glm::vec4 _textColor) {
        textColor = _textColor;
        return *this;
    }

}