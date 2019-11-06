#ifndef IBLOCK_H
#define IBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class IBlock : public Block {
public:
	IBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
