#include "ZBlock.h"
#include "Cell.h"

ZBlock::ZBlock(int levelId, bool heavy, int tx, int ty) : Block{'Z',levelId,heavy}
{
	addCell(Cell{0 + tx, 0 + ty});
	addCell(Cell{1 + tx, 0 + ty});
	addCell(Cell{1 + tx, 1 + ty});
	addCell(Cell{2 + tx, 1 + ty});
	updateBoundingBox();
}
