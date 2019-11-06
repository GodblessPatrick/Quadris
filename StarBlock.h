#ifndef STAR_BLOCK_H
#define STAR_BLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class StarBlock : public Block {
public:
	StarBlock(int levelId, bool heavy, int tx, int ty);
};
#endif
