#include "Level.h"
#include "BlockFactory.h"
#include <cstdlib>  // random

using namespace std;

Level::Level(const unsigned int id, const unsigned int I, const unsigned int J,
			 const unsigned int L, const unsigned int O, const unsigned int S,
			 const unsigned int Z, const unsigned int T) :
	id{id}, I{I}, J{J}, L{L}, O{O}, S{S}, Z{Z}, T{T}
{
	types.insert(types.end(), I, 'I');
	types.insert(types.end(), J, 'J');
	types.insert(types.end(), L, 'L');
	types.insert(types.end(), O, 'O');
	types.insert(types.end(), S, 'S');
	types.insert(types.end(), Z, 'Z');
	types.insert(types.end(), T, 'T');
}

// since except for level 0,
// the creation of blocks depends on probability,
// so we decide to implement this method in the base class,
// and make it virtual to let level 0 override its behavior
unique_ptr<Block> Level::createBlock(char type) {
	if (type == ' ') type = types[rand() % types.size()];
	return BlockFactory::createBlock(type, getId());
}

unsigned int Level::getId() const
{
	return id;	
}

Level::~Level() = default;
