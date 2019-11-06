#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <memory>
#include "Block.h"

class BlockFactory {
	BlockFactory();
public:
	static std::unique_ptr<Block> createBlock(char type, int levelId, int tx = Block::defaultTx, int ty = Block::defaultTy);
};

#endif
