#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include "Observer.h"
#include <vector>
#include <memory>
#include <map>
class Model;
#include "Window.h"

class GraphicsView : public Observer {
	const unsigned margin;  // the margin between border and text
	const unsigned indent;  // for text to align
	const unsigned nextBlockIndent;  // make "Next: " and the next block not so closer
	const unsigned textSize, cellSize;
	const unsigned width, height;
	const std::vector<std::string> textsAboveBoard;
	const unsigned offsetForBoard, offsetForNext;
	std::vector<std::vector<char>> cachedBoard;  // to optimize
	std::unique_ptr<Xwindow> xw;
	void drawText(unsigned index, const std::string &str) const;
	void drawBoard(const std::vector<std::vector<char>> &board) const;
	void drawCell(char type, int i, int j) const;
	void drawNextBlock(const std::vector<std::vector<char>> &block) const;
public:
	~GraphicsView();
	GraphicsView(Model const * const model);
	void update() override;
};

#endif
