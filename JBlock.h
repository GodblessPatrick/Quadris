#ifndef JBLOCK_H
#define JBLOCK_H

#include <memory>
#include "Block.h"
#include "BlockFactory.h"

class JBlock : public Block {
public:
	JBlock(int levelId, bool heavy, int tx, int ty);
};

#endif
