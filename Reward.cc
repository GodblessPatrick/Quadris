#include "Reward.h"

Reward::Reward(unsigned int rowsErased, unsigned int unreachableCellsIncreased, unsigned int highestCellPos) :
	rowsErased{rowsErased}, unreachableCellsIncreased{unreachableCellsIncreased}, highestCellPos{highestCellPos} {}

bool Reward::operator>(const Reward &other){

	if (rowsErased > other.rowsErased) return true;
	if (rowsErased < other.rowsErased) return false;

	if (unreachableCellsIncreased < other.unreachableCellsIncreased) return true;
	if (unreachableCellsIncreased > other.unreachableCellsIncreased) return false;

	// because higher a cell is, smaller its y-coordinate is
	// and the lower the highest cell of the hint block is better
	if (highestCellPos > other.highestCellPos) return true;
	return false;
}
