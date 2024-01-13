#include "RowContainer.h"

namespace UILib {

    RowContainer::RowContainer(float _rowHeight, float _padding, float _rowGap, glm::vec4 _color)
        : rowHeight(_rowHeight), padding(_padding), rowGap(_rowGap), Container(_color) {}
    
    void RowContainer::organizeChildren() {

        for (int i = 0; i < children.size(); i++) {
            UIBlock& child = *children[i];

            child.height = rowHeight;
            child.width = width - 2 * padding;
            child.y = y + height - padding - rowHeight * (i + 1) - rowGap * i;
            child.x = x + padding;

        }

    }

}