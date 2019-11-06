#ifndef BLOCK_H
#define BLOCK_H

#include <memory>
#include <vector>
// since we are using its methods in this header file
// so we can't forward declare it
#include "Board.h"
#include "Rectangle2D.h"
class Cell;
class Model;

class Block {
	const char type;
	std::vector<Cell> cells;
	Rectangle2D boundingBox;
	const int levelId;
	const bool heavy;
	void postMovement(const Model &model, std::vector<Cell> &&originalCells);
	void replaceCells(const std::vector<Cell> &otherCells);  // for clone()
protected:
	// For factory method design pattern
	// ctor of subclasses should all be private, and declare BlockFactory as friend
	// But to avoid directly using new (to earn marks), I just make them public at the end
	Block(char type, int levelId, bool heavy);
	void addCell(Cell &&cell);
	void updateBoundingBox();
public:
	static const int defaultTx = 0, defaultTy = Board::numSpareRows;
	static const char asteriskType = '*', hintType = '?';
	char getType() const;
	const std::vector<Cell> &getCells() const;
	std::vector<Cell> &getModifiableCells();
	const Rectangle2D &getBoundingBox() const;
	int getLevelId() const;
	// the following move operations use Board stored in Model
	// to determine if Block after operation applied is valid
	bool cc_rotate(const Model &model);  // counter-clockwise
	bool c_rotate(const Model &model);  // clockwise
	bool left(const Model &model);
	bool right(const Model &model);
	bool up(const Model &model);  // only used to display the block incurring gameover
	bool down(const Model &model);
	void drop(const Model &model);
	
	bool isVisible() const;
	const std::vector<std::vector<char>> getCharacterMatrix() const;
	bool isHeavy() const;
	virtual std::unique_ptr<Block> clone() const;
	virtual ~Block() = 0;
};

#endif
