#include "Board.h"
#include "Cell.h"
#include "Block.h"
#include <utility>  // move

using namespace std;

// this method the underlying display to contain only white spaces
void Board::reset(){
	for (auto &row : display){
		for (auto &cell : row) cell = ' ';
	}
}

// check if the block is inside this board
bool Board::contains(const Block &block) const
{
	int x, y;
	for (const Cell &cell : block.getCells()){
		x = cell.getX();
		y = cell.getY();
		if (x < 0 || x >= numCols ||
			y < 0 || y >= numTotalRows) return false;
	}
	return true;
}

// check if the block clashes with any existing blocks on the board
bool Board::clash(const Block &block) const
{
	for (const Cell &cell : block.getCells()){
		if (display[cell.getY()][cell.getX()] != ' ') return true;
	}
	return false;
}

Board::Board(){
	display.resize(Board::numTotalRows);
	for (int i=0;i<Board::numTotalRows;++i){
		display[i].resize(Board::numCols, ' ');
	}
}

const vector<vector<char>> &Board::getDisplay() const
{
	return display;
}

list<size_t> Board::getCompletedRowsId() const
{
	list<size_t> res;
	for (size_t i=0;i<display.size();++i){
		// check if any row is completed
		for (size_t j=0;j<display[i].size();++j){
			// if a row contains any white spaces, then it's not completed
			if (display[i][j] == ' ') break;
			// if the current row does not contain any white spaces
			if (j == display[i].size() - 1) res.push_back(i);
		}
	}
	return res;
}

bool Board::isValid(const Block &block) const
{
	if (contains(block) && !clash(block)) return true;
	else return false;
}

void Board::clear(const Block &block){
	for (const Cell &cell : block.getCells()){
		display[cell.getY()][cell.getX()] = ' ';
	}
}

// we can't directly use block.getType() to omit type argument
// because we may be adding a hint block
void Board::add(const Block &block, char type){
	for (const Cell &cell : block.getCells()){
		if (cell.isVisible()) display[cell.getY()][cell.getX()] = type;
	}
}

// clear the display then inflate it with the provided blocks
void Board::update(const vector<unique_ptr<Block>> &blocks){
	reset();
	for (const auto &block : blocks) add(*block, block->getType());
}

bool Board::isEmptyRow(int i) const
{
	for (unsigned int j=0;j<display[i].size();++j){
		if (display[i][j] != ' ') return false;
	}
	return true;
}

unsigned int Board::numUnreachableCells() const
{
	unsigned int res = 0;
	
	// iterate through columns
	for (int j=0;j<Board::numCols;++j){
		bool reachable = true;
		// skip the spare rows
		for (unsigned int i=Board::numSpareRows;i<display.size();++i){
			// this cell is empty
			if (display[i][j] == ' '){
				// and there is a cell above it that is not empty
				if (!reachable) ++res;
			}
			// all the cells below this cell is unreachable
			else reachable = false;
		}
	}

	return res;
}
