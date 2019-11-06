#ifndef ZBLOCK_H
#define ZBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class ZBlock : public Block {
public:
	ZBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
