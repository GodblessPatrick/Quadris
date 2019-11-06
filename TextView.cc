#include "TextView.h"
#include "Model.h"
#include "Board.h"
#include "Block.h"
#include <vector>
#include <iostream>

using namespace std;

TextView::TextView(Model const * const model) : Observer{model} {}

void TextView::printBorder() const
{
	for (int i=0;i<Board::numCols;++i) cout << '-';
	cout << endl;
}

void TextView::printGrid(const vector<vector<char>> &grid) const
{
	for (auto &row : grid){
		for (auto &cell : row){
			cout << cell;
		}
		cout << endl;
	}
}

void TextView::update(){

	cout << "Level: " << model->getCurLevelId() << endl;
	cout << "Score: " << model->getCurScore() << endl;
	cout << "Hi Score: " << model->getMaxScore() << endl;

	printBorder();
	printGrid(model->getBoard().getDisplay());
	printBorder();

	cout << "Next:" << endl;
	// since printGird() onyl accepts reference, so we need to create a lvalue
	vector<vector<char>> nextBlock = model->getNextBlock().getCharacterMatrix(); 
	printGrid(nextBlock);

	if (model->isGameover()) cout << "Game Over!" << endl;
}
