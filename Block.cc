#include "Block.h"
#include "Board.h"
#include "Cell.h"
#include "Rectangle2D.h"
#include "Model.h"
#include "QuadrisException.h"
#include "BlockFactory.h"  // clone()
#include <utility>  // move
#include <climits>  // INT_MIN, INT_MAX
#include <cassert>
#include <iostream>
using namespace std;

void Block::postMovement(const Model &model, vector<Cell> &&originalCells){
	if (model.getBoard().isValid(*this)){
		updateBoundingBox();
	}
	else{
		cells = move(originalCells);
		throw QuadrisException{};
	}
}

Block::Block(char type, int levelId, bool heavy) : type{type}, levelId{levelId}, heavy{heavy} {}

void Block::addCell(Cell &&cell){
	cells.emplace_back(cell);	
}

void Block::updateBoundingBox(){
	int x, y, minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;
	for (const Cell &cell : cells){
		x = cell.x;
		y = cell.y;
		minX = x < minX ? x : minX;
		minY = y < minY ? y : minY;
		maxX = x > maxX ? x : maxX;
		maxY = y > maxY ? y : maxY;
	}
	boundingBox.reset(minX, minY, maxX - minX + 1, maxY - minY + 1);
}

void Block::replaceCells(const vector<Cell> &otherCells){
	
	// clear the original cells
	cells.clear();

	for (const Cell &cell : otherCells){
		cells.push_back(cell);
	}

	updateBoundingBox();
}

char Block::getType() const
{
	return type;
}

const Rectangle2D &Block::getBoundingBox() const
{
	return boundingBox;
}

const vector<Cell> &Block::getCells() const
{
	return cells;
}

vector<Cell> &Block::getModifiableCells(){
	return cells;	
}

int Block::getLevelId() const
{
	return levelId;
}

bool Block::cc_rotate(const Model &model){

	vector<Cell> originalCells{cells};
	
	// the lower-left corner of the bounding box
	Cell pivot(boundingBox.getX(), boundingBox.getY() + boundingBox.getH() - 1);
	int x, y, px = pivot.getX(), py = pivot.getY();
	
	for (Cell &cell : cells){
		x = cell.x;
		y = cell.y;
		cell.x = px + (boundingBox.getH() - 1) - (py - y);
		cell.y = py - (x - px);
	}

	try { postMovement(model, move(originalCells)); }
	catch (QuadrisException) { return false; }
	return true;
}

bool Block::c_rotate(const Model &model){

	vector<Cell> originalCells{cells};
	
	// the lower-left corner of the bounding box
	Cell pivot(boundingBox.getX(), boundingBox.getY() + boundingBox.getH() - 1);
	int x, y, px = pivot.getX(), py = pivot.getY();
	
	for (Cell &cell : cells){
		x = cell.x;
		y = cell.y;
		cell.x = px + (py - y);
		cell.y = py - (boundingBox.getW() - 1) + (x - px);
	}

	try { postMovement(model, move(originalCells)); }
	catch (QuadrisException) { return false; }
	return true;
}

bool Block::left(const Model &model){

	vector<Cell> originalCells{cells};
	for (Cell &cell : cells) cell.x = cell.x - 1;

	try { postMovement(model, move(originalCells)); }
	catch (QuadrisException) { return false; }
	return true;
}

bool Block::right(const Model &model){

	vector<Cell> originalCells{cells};
	for (Cell &cell : cells) cell.x = cell.x + 1;

	try { postMovement(model, move(originalCells)); }
	catch (QuadrisException) { return false; }
	return true;
}

bool Block::up(const Model &model){

	vector<Cell> originalCells{cells};
	for (Cell &cell : cells) cell.y = cell.y - 1;

	// because this method is used to move the block that incurs gameover up enough to display it,
	// so during moving it up, it is surely to be invalid,
	// and no need to rollback changes when it is invalid
	if (model.getBoard().isValid(*this)) return true;
	else return false;
}

bool Block::down(const Model &model){

	vector<Cell> originalCells{cells};
	for (Cell &cell : cells) cell.y = cell.y + 1;

	try { postMovement(model, move(originalCells)); }
	catch (QuadrisException) { return false; }
	return true;
}

void Block::drop(const Model &model){
	while (down(model));
}

bool Block::isVisible() const
{
	for (const Cell &cell : cells){
		if (cell.isVisible()) return true;
	}
	return false;
}

// for views to draw next block
const vector<vector<char>> Block::getCharacterMatrix() const
{
	const int numRows = boundingBox.getH();
	const int numCols = boundingBox.getW();

	// initialization
	vector<vector<char>> res;
	res.resize(numRows);
	for (int i=0;i<numRows;++i){
		res[i].resize(numCols, ' ');
	}

	for (const Cell &cell : cells){
		res[cell.y - boundingBox.getY()][cell.x - boundingBox.getX()] = type;
	}

	return res;
}

bool Block::isHeavy() const
{
	return heavy;	
}

unique_ptr<Block> Block::clone() const
{
	unique_ptr<Block> res = BlockFactory::createBlock(type, levelId);
	res->replaceCells(cells);
	return res;
}

Block::~Block() = default;

