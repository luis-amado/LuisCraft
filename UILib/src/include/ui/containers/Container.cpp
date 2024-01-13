#include "Container.h"

namespace UILib {

    Container::Container(glm::vec4 _color)
        : UIBlock(_color) {}

    void Container::addChild(UIBlock* newChild) {
        children.push_back(newChild);
        organizeChildren();

        for (UIBlock* child : children) {
            child->onBoxUpdated();
        }
    }

    void Container::updateBlock(UIBlock& parent) {
        constraints.build(parent.x, parent.y, parent.width, parent.height);
        x = constraints.getX();
        y = constraints.getY();
        width = constraints.getWidth();
        height = constraints.getHeight();
        onBoxUpdated();
        organizeChildren();

        for (UIBlock* child : children) {
            child->onBoxUpdated();
            child->updateChildren();
        }

    }


}