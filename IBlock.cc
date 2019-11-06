#include "IBlock.h"
#include "Cell.h"

IBlock::IBlock(int levelId, bool heavy, int tx, int ty) : Block{'I', levelId, heavy}
{
	addCell(Cell{0 + tx, 0 + ty});
	addCell(Cell{1 + tx, 0 + ty});
	addCell(Cell{2 + tx, 0 + ty});
	addCell(Cell{3 + tx, 0 + ty});
	updateBoundingBox();
}
