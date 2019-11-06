#ifndef OBLOCK_H
#define OBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class OBlock : public Block {
public:
	OBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
