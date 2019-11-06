#ifndef SBLOCK_H
#define SBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class SBlock : public Block {
public:
	SBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
