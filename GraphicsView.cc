#include <iostream>
#include "GraphicsView.h"
#include "Window.h"
#include <memory>
#include <map>
#include "Block.h"
#include <vector>
#include <string>
#include "Model.h"
using namespace std;

// colorss pairs of colors and char types
std::map<char, string> colors = {
	{' ', "White"},
	{'I', "Light Sky Blue"},
	{'J', "Light Sea Green"},
	{'L', "Light Salmon"},
	{'O', "Light Pink"},
	{'S', "Light Green"},
	{'T', "Light Goldenrod"},
	{'Z', "Light Blue"},
	{'*', "Brown"},
	{'?', "Black"},
};

void GraphicsView::drawText(unsigned index, const string &str) const
{
	// clear the text first
    xw->fillRectangle(indent, textSize * index, width - indent, textSize, colors[' ']);
	xw->drawString(indent, textSize * (index + 1), str);
}

void GraphicsView::drawBoard(const vector<vector<char>> &board) const
{
	// draw the board
	for (unsigned i = 0; i < board.size(); ++i) {
	    for (unsigned j = 0; j < board[i].size(); ++j) {
			// only draw the cell if it changes
	    	if (board[i][j] != cachedBoard[i][j]) {
				drawCell(board[i][j], i, j);
	    	} 
	    }
	}
}

void GraphicsView::drawCell(char type, int i, int j) const
{
	xw->fillRectangle(j * cellSize, offsetForBoard + i * cellSize, cellSize, cellSize, colors[type]);
}

void GraphicsView::drawNextBlock(const vector<vector<char>> &block) const
{
	// clear the previous next block first
	// 4 for the max width of a next block, 2 for the max height
	xw->fillRectangle(nextBlockIndent, offsetForNext, cellSize * 4, cellSize * 2, colors[' ']);

	for (unsigned i = 0; i < block.size(); ++i) {                                
		for (unsigned j = 0; j < block[i].size(); ++j) {                       
	      	xw->fillRectangle(nextBlockIndent + j * cellSize, offsetForNext + i * cellSize,
				cellSize, cellSize, colors[block[i][j]]);                                                     
		}
	}
}

// ctor of GraphicsView
GraphicsView::GraphicsView(Model const * const model): Observer{model},
	margin{5}, indent{100}, nextBlockIndent{60}, textSize{20}, cellSize{30},
	width{cellSize * Board::numCols},
	// For text: level, current score, max score, message, 
	// upper board border, lower board border, next block
	// For cell: +2 for next block
	height{textSize * 7 + cellSize * (Board::numTotalRows + 2)},
	textsAboveBoard{"Level: ", "Score: ", "Hi Score: ", "Message: "},
	offsetForBoard{textSize * ((unsigned)textsAboveBoard.size() + 1)},  // +1 for upper border
	// +3 for upper border, lower border, and "Next" text
	offsetForNext{((unsigned)textsAboveBoard.size() + 3) * textSize + cellSize * Board::numTotalRows},
	cachedBoard{model->getBoard().getDisplay()}
{
	// tell Xwindow what colors we need
	vector<string> colorNames;
	for (const auto &p : colors) colorNames.push_back(p.second);
	xw = make_unique<Xwindow>(width, height, colorNames);

	// initialize the pixmap to white
	xw->fillRectangle(0, 0, width, height, colors[' ']);

	// draw the text descriptions
	for (unsigned i=0;i<textsAboveBoard.size();++i){
		xw->drawString(margin, textSize * (i + 1), textsAboveBoard[i]);
	}

	// draw the upper border
	int y = offsetForBoard - (textSize / 2);
	xw->drawLine(0, y, width, y);
	
	// draw the lower border
	y = offsetForBoard + cellSize * Board::numTotalRows + (textSize / 2);
	xw->drawLine(0, y, width, y);

	xw->drawString(margin, offsetForNext, "Next: ");

	// Because when update() is invoked at the very first time
	// cachedBoard will be identical with the board stored in model,
	// so drawBoard() invoked by update() won't draw anything.
	// However, we know that there will be only one block on the board, namely the undropped block
	// so we can draw it here
	const vector<vector<char>> block = model->getUndroppedBlock().getCharacterMatrix();
	for (unsigned i=0;i<block.size();++i){
		for (unsigned j=0;j<block[i].size();++j){
			xw->fillRectangle(j * cellSize, offsetForBoard + cellSize * (Board::numSpareRows + i),
				cellSize, cellSize, colors[block[i][j]]);
		}
	}
}

void GraphicsView::update(){

	string gameover = model->isGameover() ? "GAME OVER" : "";

	// draw the texts above board
	vector<string> strs{to_string(model->getCurLevelId()),
		to_string(model->getCurScore()), to_string(model->getMaxScore()), move(gameover)};
	for (unsigned i=0;i<strs.size();++i){
		drawText(i, strs[i]);
	}

	// draw the board
	const vector<vector<char>> &curBoard = model->getBoard().getDisplay();
	drawBoard(curBoard);
	// update cache
	cachedBoard = curBoard;

	// draw the next block
	drawNextBlock(model->getNextBlock().getCharacterMatrix());

	// flush all the drawings currently in pixmap to screen
	xw->flush();
}

GraphicsView::~GraphicsView() {
	xw.release();
}
