#ifndef TBLOCK_H
#define TBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class TBlock : public Block {
public:
	TBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
