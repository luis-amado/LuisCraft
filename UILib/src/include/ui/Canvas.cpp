#include "Canvas.h"


#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "text/Text.h"

namespace UILib {

    Canvas::Canvas(float x, float y, float width, float height)
        : UIBlock(x, y, width, height), uiShader("res/shaders/ui.vs", "res/shaders/ui.fs"), projection(glm::ortho(0.0f, width, 0.0f, height)) {
        Text::init();
    }

    Canvas::~Canvas() {
        UIQuad::destroy();
        Text::destroy();
    }

    void Canvas::render() {

        uiShader.use();
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (UIBlock* child : children) {
            child->renderBlock(uiShader, projection, *this);
        }
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }
    
    void Canvas::updateSize(float newWidth, float newHeight) {
        projection = glm::ortho(0.0f, newWidth, 0.0f, newHeight);
        constraints.setWidth(newWidth);
        constraints.setHeight(newHeight);
        width = newWidth;
        height = newHeight;
        for (UIBlock* child : children) {
            child->updateBlock(*this);
        }
    }

}