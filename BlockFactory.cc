#include "BlockFactory.h"
#include "QuadrisException.h"
#include "OBlock.h"
#include "IBlock.h"
#include "JBlock.h"
#include "LBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "StarBlock.h"
#include <memory>

using namespace std;

unique_ptr<Block> BlockFactory::createBlock(char type, int levelId, int tx, int ty){

	bool heavy = (levelId >= 3) ? true : false;

	switch (type){
		case 'O':
			return make_unique<OBlock>(levelId, heavy, tx, ty);
			break;
		case 'I':
			return make_unique<IBlock>(levelId, heavy, tx, ty);
			break;
		case 'J':
			return make_unique<JBlock>(levelId, heavy, tx, ty);
			break;
		case 'L':
			return make_unique<LBlock>(levelId, heavy, tx, ty);
			break;
		case 'S':
			return make_unique<SBlock>(levelId, heavy, tx, ty);
			break;
		case 'T':
			return make_unique<TBlock>(levelId, heavy, tx, ty);
			break;
		case 'Z':
			return make_unique<ZBlock>(levelId, heavy, tx, ty);
			break;
		case Block::asteriskType:
			return make_unique<StarBlock>(levelId, heavy, tx, ty);
			break;
		default:
			throw QuadrisException{"Invalid block type"};
	}
}
