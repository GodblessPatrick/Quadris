#include "TBlock.h"
#include "Cell.h"

TBlock::TBlock(int levelId, bool heavy, int tx, int ty) : Block{'T',levelId,heavy}
{
	addCell(Cell{0 + tx, 0 + ty});
	addCell(Cell{1 + tx, 0 + ty});
	addCell(Cell{2 + tx, 0 + ty});
	addCell(Cell{1 + tx, 1 + ty});
	updateBoundingBox();
}
