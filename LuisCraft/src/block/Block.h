#pragma once

#include <string>

#include "../init/BlockTextures.h"

class Block {

public:

    Block();
    Block(BlockTextures _textures);

    void init(std::string _registryName, unsigned int _blockIndex);

    // Attribute setters
    Block& notSolid();
    Block& emitsLight(unsigned char _light);

    // Attribute getters
    inline unsigned int getBlockIndex() const { return blockIndex; }
    inline bool isSolid() const { return solid; }
    inline unsigned char getLightLevel() const { return light; }

    const BlockTextures& getTextures() const { return textures; }

private:
    std::string registryName;

    unsigned int blockIndex;

    // block attributes
    bool solid = true;
    unsigned char light = 0;
    BlockTextures textures;

};