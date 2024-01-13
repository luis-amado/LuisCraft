#include "UIBlock.h"

#include "constraints/PixelConstraint.h"

namespace UILib {

    UIBlock::UIBlock(float x, float y, float w, float h) : UIQuad(x, y, w, h), constraints(x, y, w, h) {}

    UIBlock::UIBlock(glm::vec4 _color) : UIQuad(0, 0, 0, 0), color(_color) {}

    UIBlock::~UIBlock() {
        for (UIBlock* block : children) {
            delete block;
        }
    }

    void UIBlock::renderBlock(UIShader& shader, const glm::mat4& projection, const UIBlock& parent) {
        shader.setUniform4f("color", color);
        shader.setUniform4f("parent", { parent.x, parent.y, parent.width, parent.height });
        draw(shader, projection);
        renderAdditional(shader, projection, parent);
        for (UIBlock* child : children) {
            child->renderBlock(shader, projection, *this);
        }
    }

    void UIBlock::updateBlock(UIBlock& parent) {
        constraints.build(parent.x, parent.y, parent.width, parent.height);
        x = constraints.getX();
        y = constraints.getY();
        width = constraints.getWidth();
        height = constraints.getHeight();
        onBoxUpdated();
        for (UIBlock* child : children) {
            child->updateBlock(*this);
        }
    }

    void UIBlock::updateChildren() {
        for (UIBlock* child : children) {
            child->updateBlock(*this);
        }
    }

    void UIBlock::addChild(UIBlock* newChild) {
        children.push_back(newChild);
        newChild->constraints.build(x, y, width, height);
        newChild->x = newChild->constraints.getX();
        newChild->y = newChild->constraints.getY();
        newChild->width = newChild->constraints.getWidth();
        newChild->height = newChild->constraints.getHeight();
        newChild->onBoxUpdated();
    }

    UIBlock& UIBlock::fillParent(int padding) {
        return fillParent(padding, padding, padding, padding);
    }

    UIBlock& UIBlock::fillParent(int paddingV, int paddingH) {
        return fillParent(paddingV, paddingH, paddingV, paddingH);
    }

    UIBlock& UIBlock::fillParent(int paddingT, int paddingR, int paddingB, int paddingL) {

        constraints.top = new PixelConstraint(paddingT);
        constraints.right = new PixelConstraint(paddingR);
        constraints.bottom = new PixelConstraint(paddingB);
        constraints.left = new PixelConstraint(paddingL);

        return *this;
    }

    UIBlock& UIBlock::setTop(Constraint* _top) {
        constraints.top = _top;
        return *this;
    }
    UIBlock& UIBlock::setLeft(Constraint* _left) {
        constraints.left = _left;
        return *this;
    }
    UIBlock& UIBlock::setRight(Constraint* _right) {
        constraints.right = _right;
        return *this;
    }
    UIBlock& UIBlock::setBottom(Constraint* _bottom) {
        constraints.bottom = _bottom;
        return *this;
    }
    UIBlock& UIBlock::setCenterH(Constraint* _centerH) {
        constraints.centerH = _centerH;
        return *this;
    }
    UIBlock& UIBlock::setCenterV(Constraint* _centerV) {
        constraints.centerV = _centerV;
        return *this;
    }
    UIBlock& UIBlock::setWidth(Constraint* _width) {
        constraints.width = _width;
        return *this;
    }
    UIBlock& UIBlock::setHeight(Constraint* _height) {
        constraints.height = _height;
        return *this;
    }

}