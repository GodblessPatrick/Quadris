#include "JBlock.h"
#include "Cell.h"

JBlock::JBlock(int levelId, bool heavy, int tx, int ty) : Block{'J', levelId, heavy}
{
	addCell(Cell{0 + tx, 0 + ty});
	addCell(Cell{0 + tx, 1 + ty});
	addCell(Cell{1 + tx, 1 + ty});
	addCell(Cell{2 + tx, 1 + ty});
	updateBoundingBox();
}
