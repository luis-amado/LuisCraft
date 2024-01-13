#pragma once

#include <unordered_map>
#include <string>
#include <utility>

#include "../block/Block.h"

class BlockRegistry {

public:

    ~BlockRegistry();

    std::unordered_map<std::string, Block*> blockMap;
    std::vector<Block*> blocks;

    template <typename T>
    T& registerBlock(std::string registryName, Block* block) {

        block->init(registryName, blocks.size());
        blocks.push_back(block);
        blockMap[registryName] = block;
        return *block;

    }

};