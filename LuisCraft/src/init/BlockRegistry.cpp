#include "BlockRegistry.h"

BlockRegistry::~BlockRegistry() {

    for (auto& [registryName, block] : blockMap) {
        delete block;
    }

}