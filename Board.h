#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>
#include <list>

class Block;

class Board {
	std::vector<std::vector<char>> display;
	void reset();
	bool contains(const Block &block) const;
	bool clash(const Block &block) const;
	// for hint
	bool isEmptyRow(int i) const;
public:
	Board();
	static const int numCols = 11, numGameRows = 15, numSpareRows = 3;
	static const int numTotalRows = numGameRows + numSpareRows;
	const std::vector<std::vector<char>> &getDisplay() const;
	std::list<size_t> getCompletedRowsId() const;
	bool isValid(const Block &block) const;
	void clear(const Block &block);
	void add(const Block &block, char type);
	void update(const std::vector<std::unique_ptr<Block>> &blocks);
	// these tow methods are for hint
	unsigned int numUnreachableCells() const;
};

#endif
