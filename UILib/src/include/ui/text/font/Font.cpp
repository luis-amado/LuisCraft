#include "Font.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace UILib {

    Font::Font(const std::string& filepath) {

        std::ifstream f(filepath.c_str());
        json fontData = json::parse(f);

        /*std::string property;
        std::string value;

        std::string input;
        int dividerPos;

        std::string texturefile;

        while (property != "chars") {

            f >> input;
            dividerPos = input.find_first_of('=');
            property = input.substr(0, dividerPos);
            if (dividerPos != -1)
                value = input.substr(dividerPos + 1);
            else
                value = "";

            if (property == "base") {
                base = atoi(value.c_str());
            } else if (property == "size") {
                size = atoi(value.c_str());
            } else if (property == "file") {
                texturefile = value.substr(1, value.length() - 2);
            }

        }

        std::string line;
        std::getline(f, line);
        while (std::getline(f, line)) {

            std::stringstream str(line);
            str >> input;
            if (input != "char") continue;

            Character c;

            str >> input;
            c.id = atoi(input.c_str() + 3);

            str >> input;
            c.x = atoi(input.c_str() + 2);

            str >> input;
            c.y = atoi(input.c_str() + 2);

            str >> input;
            c.width = atoi(input.c_str() + 6);

            str >> input;
            c.height = atoi(input.c_str() + 7);

            str >> input;
            c.xoffset = atoi(input.c_str() + 8);

            str >> input;
            c.yoffset = atoi(input.c_str() + 8);

            str >> input;
            c.xadvance = atoi(input.c_str() + 9);

            characters[c.id] = c;

        }*/

        base = fontData["config"]["base"];
        size = fontData["config"]["size"];
        lineHeight = fontData["config"]["charHeight"];

        // Record available characters (symbols)
        for (json symbol : fontData["symbols"]) {
            Character c;
            int id = symbol["id"];
            c.id = (char)id;
            c.x = symbol["x"];
            c.y = symbol["y"];
            c.width = symbol["width"];
            c.height = symbol["height"];
            c.xoffset = symbol["xoffset"];
            c.yoffset = symbol["yoffset"];
            c.xadvance = symbol["xadvance"];

            characters[c.id] = c;
        }

        // Texture
        std::string texfilepath = "res/textures/font/" + (std::string)fontData["config"]["textureFile"];
        //std::string texfilepath = "res/textures/font/" + texturefile;
        texture.generate(texfilepath.c_str(), 1);

    }

    void Font::use() const {
        texture.bind();
    }

    const Character& Font::getChar(char character) const {
        return characters.at(character);
    }

}