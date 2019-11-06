#include "SBlock.h"
#include "Cell.h"

SBlock::SBlock(int levelId, bool heavy, int tx, int ty) : Block{'S',levelId,heavy}
{
	addCell(Cell{1 + tx, 0 + ty});
	addCell(Cell{2 + tx, 0 + ty});
	addCell(Cell{0 + tx, 1 + ty});
	addCell(Cell{1 + tx, 1 + ty});
	updateBoundingBox();
}
