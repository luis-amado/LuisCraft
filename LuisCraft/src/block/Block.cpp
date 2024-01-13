#include "Block.h"

Block::Block()
    : blockIndex(std::numeric_limits<unsigned int>::max()), textures(BlockTextures::all(0)) {}

Block::Block(BlockTextures _textures)
    : blockIndex(std::numeric_limits<unsigned int>::max()), textures(_textures) {}

void Block::init(std::string _registryName, unsigned int _blockIndex) {
    registryName = _registryName;
    blockIndex = _blockIndex;
}

Block& Block::notSolid() {
    solid = false;
    return *this;
}

Block& Block::emitsLight(unsigned char _light) {
    light = _light;
    return *this;
}