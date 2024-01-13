#include "Blocks.h"

BlockRegistry Blocks::registry;

const Block& Blocks::AIR = registry.registerBlock<Block>("air", new Block()).notSolid();
const Block& Blocks::GRASS = registry.registerBlock<Block>("grass", new Block(BlockTextures::sideUpDown(1, 2, 0)));
const Block& Blocks::DIRT = registry.registerBlock<Block>("dirt", new Block(BlockTextures::all(0)));
const Block& Blocks::STONE = registry.registerBlock<Block>("stone", new Block(BlockTextures::all(3)));
const Block& Blocks::DEEPSLATE_BRICKS = registry.registerBlock<Block>("deepslate_bricks", new Block(BlockTextures::all(4)));
const Block& Blocks::GLOWSTONE = registry.registerBlock<Block>("glowstone", new Block(BlockTextures::all(5))).emitsLight(15);