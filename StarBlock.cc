#include "StarBlock.h"
#include "Cell.h"
using namespace std;

StarBlock::StarBlock(int levelId, bool heavy, int tx, int ty) : Block{'*', levelId, heavy} 
{
	addCell(Cell{5 + tx,0 + ty});
	updateBoundingBox();
}
