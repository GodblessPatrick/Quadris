#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>
#include <list>
#include "Subject.h"
#include "Board.h"
#include "Block.h"
#include "Level.h"

class Model : public Subject{
	bool gameover;
	Board board;
	std::vector<std::unique_ptr<Block>> droppedBlocks; 
	std::vector<std::unique_ptr<Level>> levels;
	Level *curLevel;
	unsigned int numAccumulatedBlocks;  // only matters for level 4
	unsigned int curScore;
	unsigned int maxScore;
	std::unique_ptr<Block> undroppedBlock;
	std::unique_ptr<Block> nextBlock;
	std::vector<char> noRandomSequence;  // only matters for level 3 and 4
	unsigned int curIdForNRS;
	bool random;  // only matters for level 3 and 4 
	std::unique_ptr<Block> hintBlock;
	void addScore(const unsigned int scoreToBeAdded);
	static bool contains(const std::list<size_t> &l, const size_t value);
	static int getOffset(const std::list<size_t> &l, const size_t value);
	void clearRows(const std::list<size_t> &indices);
	void moveUpperBlocks(const std::list<size_t> &completedRowsId);
	void reset();
	void updateBlocksAndScore(const std::list<size_t> &completedRowsId);
	std::unique_ptr<Block> findHint();
public:
	Model(std::vector<char> &&sequence, int levelId, int seed);
	bool isGameover() const;
	const Board &getBoard() const;
	int getCurLevelId() const;
	unsigned int getCurScore() const;
	unsigned int getMaxScore() const;
	Block &getUndroppedBlock() const;  // for move operations
	void setUndroppedBlock(std::unique_ptr<Block> newUndroppedBlock);  // for replace operations
	const Block &getNextBlock() const;
	void levelUp();
	void levelDown();
	void preMovement();
	void postMovement();
	void dropBlock();
	void setNoRandomSequence(std::vector<char> &&sequence);
	void restoreRandomness();
	void restartGame();
	void showHint();
	void clearHint();
};

#endif
