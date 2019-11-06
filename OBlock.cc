#include "OBlock.h"
#include "Cell.h"

OBlock::OBlock(int levelId, bool heavy, int tx, int ty) : Block{'O', levelId, heavy}
{
	addCell(Cell{0 + tx, 0 + ty});
	addCell(Cell{1 + tx, 0 + ty});
	addCell(Cell{0 + tx, 1 + ty});
	addCell(Cell{1 + tx, 1 + ty});
	updateBoundingBox();
}

