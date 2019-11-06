#include "Level0.h"
#include "BlockFactory.h"

using namespace std;

Level0::Level0(vector<char> sequence) : Level{0}, sequence{sequence}, nextBlockId{0} {}

unique_ptr<Block> Level0::createBlock(char type){
	// if the caller didn't specify the type
	if (type == ' '){
		type = sequence[nextBlockId];
		// if we are at the end of the sequence
		// then re-use it from the beginning
		nextBlockId = (nextBlockId == sequence.size() - 1) ? 0 : nextBlockId + 1;
	}
	return BlockFactory::createBlock(type, getId());
}
