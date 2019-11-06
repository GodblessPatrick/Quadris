#ifndef CELL_H
#define CELL_H

class Block;
class Model;

class Cell {
	int x, y;
	bool visible;
public:
	Cell(int x, int y);
	int getX() const;
	int getY() const;
	bool isVisible() const;
	void disappear();
	friend Block;
	// in moveUpperBlocks()
	friend Model;
};

#endif
