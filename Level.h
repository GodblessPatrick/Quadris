#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
class Block;

class Level {
	const unsigned int id;
	// the relative probability of generating the corresponding type of block
	const unsigned int I, J, L, O, S, Z, T;
	std::vector<char> types;
public:
	// because level 0 does not generate blocks depending on probabiity,
	// it does not make sense for level 0 to provide arguments I, J,...etc,
	// so we make these arguments have default values
	Level(const unsigned int id, const unsigned int I = 0, const unsigned int J = 0,
		  const unsigned int L = 0, const unsigned int O = 0, const unsigned int S = 0,
		  const unsigned int Z = 0, const unsigned int T = 0);
	// create the specified type of block if type argument is provided
	virtual std::unique_ptr<Block> createBlock(char type = ' ');
	unsigned int getId() const;
	virtual ~Level();
};

#endif
