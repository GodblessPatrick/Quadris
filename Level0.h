#ifndef LEVEL0_H
#define LEVEL0_H

#include <memory>
#include <vector>
#include "Level.h"
class Block;

class Level0 : public Level {
	std::vector<char> sequence;
	unsigned int nextBlockId;
public:
	Level0(std::vector<char> sequence);
	std::unique_ptr<Block> createBlock(char type) override;
};

#endif
