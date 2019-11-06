#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "Observer.h"
#include <vector>
class Model;

class TextView : public Observer{
	void printBorder() const;
	void printGrid(const std::vector<std::vector<char>> &grid) const;
public:
	TextView(Model const * const model);	
	void update() override;
};

#endif

