#ifndef REWARD_H
#define REWARD_H

class Reward {
	unsigned int rowsErased, unreachableCellsIncreased, highestCellPos;
public:
	Reward(unsigned int rowsErased, unsigned int unreachableCellsIncreased, unsigned int highestCellPos);
	bool operator>(const Reward &other);
};

#endif
