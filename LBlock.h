#ifndef LBLOCK_H
#define LBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class LBlock : public Block {
public:
	LBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
