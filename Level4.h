#ifndef LEVEL4_H
#define LEVEL4_H

#include "Level.h"

class Level4 : public Level {
public:
	// every time dropping threshold blocks in level 4 without clearing a line
	// an obstacle block will be dropped on the center column of the board
	static const unsigned int threshold = 5;
	Level4();
};

#endif

