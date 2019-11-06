#include "Model.h"
#include "Block.h"
#include "Cell.h"
#include "Rectangle2D.h"
#include "QuadrisException.h"

#include "Level.h"
#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"

#include "BlockFactory.h"  // to create hint block with tx and ty

#include "Reward.h"  // to represent the reward of a possible hint

#include <cstdlib>  // random
#include <cassert>
#include <algorithm>  // find

#include <iostream>

using namespace std;

void Model::addScore(const unsigned int scoreToBeAdded){
	curScore += scoreToBeAdded;
	if (curScore > maxScore) maxScore = curScore;
}

// check if l contains the value
bool Model::contains(const list<size_t> &l, const size_t value){
	return (find(l.begin(), l.end(), value) != l.end());
}

// return the number of elements in l that is larger than value
int Model::getOffset(const list<size_t> &completedRowsId, const size_t y_value){
	int counter = 0;
	for (const auto &element : completedRowsId){

		// a cell on a completed row should not be passed in
		assert (element != y_value);

		// if this completed row is below the cell
		if (element > y_value) ++counter;
	}
	return counter;
}

// This method do the following two things
// 1. set the cells on the index-th row to be invisible
// 2. if any block becomes invisible, remove it from blocks and update score
void Model::clearRows(const list<size_t> &indices){
	vector<unique_ptr<Block>>::iterator it;
	for (it=droppedBlocks.begin();it!=droppedBlocks.end();++it){
		for (Cell &cell : (*it)->getModifiableCells()){
			// if this cell is at a completed row, then make it disappear
			if (Model::contains(indices, cell.getY())) cell.disappear();
		}
		// if every cell of this block is invisible
		if (!(*it)->isVisible()){

			// update score for this block
			unsigned int levelIdPlusOne = (*it)->getLevelId() + 1;
			addScore(levelIdPlusOne * levelIdPlusOne);

			// remove it from blocks
			droppedBlocks.erase(it);

			// now it points to the next block of the removed block
			// so we need to decrement it
			--it;
		}
	}
}

void Model::moveUpperBlocks(const list<size_t> &completedRowsId){
	for (auto &block : droppedBlocks){
		for (auto &cell : block->getModifiableCells()){
			// only move the visible cells
			if (cell.isVisible()){
				int offset = getOffset(completedRowsId, cell.getY()); 
				cell.y += offset;
			}
		}
	}
}

// set all the states to default
void Model::reset(){
	
	numAccumulatedBlocks = 0;
	
	gameover = false;

	curScore = 0;

	undroppedBlock = curLevel->createBlock();
	board.add(*undroppedBlock, undroppedBlock->getType());
	nextBlock = curLevel->createBlock();

	random = true;
}

Model::Model(vector<char> &&sequence, int levelId, int seed)
{
	srand(seed);

	levels.emplace_back(make_unique<Level0>(sequence));
	levels.emplace_back(make_unique<Level1>());
	levels.emplace_back(make_unique<Level2>());
	levels.emplace_back(make_unique<Level3>());
	levels.emplace_back(make_unique<Level4>());

	curLevel = levels[levelId].get();

	maxScore = 0;

	// hintBlock points to null now
	// noRandomSequence, and board are empty now

	reset();
}

bool Model::isGameover() const
{
	return gameover;
}

const Board &Model::getBoard() const
{
	return board;	
}

int Model::getCurLevelId() const
{
	return curLevel->getId();
}

unsigned int Model::getCurScore() const
{
	return curScore;
}

unsigned int Model::getMaxScore() const
{
	return maxScore;
}

Block &Model::getUndroppedBlock() const
{
	return *undroppedBlock;
}

void Model::setUndroppedBlock(unique_ptr<Block> newUndroppedBlock)
{
	if (!gameover){
		// clear the current undroppedBlock first to let board
		// determine whether the new undropped block is valid
		board.clear(*undroppedBlock);	
		if (board.isValid(*newUndroppedBlock)){
	
			undroppedBlock.swap(newUndroppedBlock);
			// the previously undropped block will be deallocated
			// when newUndroppedBlock goes out of scope
	
			// add the new undropped block to the board
			board.add(*undroppedBlock, undroppedBlock->getType());	
		}
		else{
			// restore the old undropped block to the board
			board.add(*undroppedBlock, undroppedBlock->getType());	
			string message = "The undropped block can't be replace with a "
						   // use to_string directly will convert the single char to its ascii code as string
						   + string(1, newUndroppedBlock->getType()) + " block.";
			throw QuadrisException{move(message)};
		}
	}
}

const Block &Model::getNextBlock() const
{
	return *nextBlock;
}

void Model::levelUp(){
	if (curLevel->getId() == levels.size() - 1){
		throw QuadrisException{"The current level is already the highest level"};
	}
	else{
		curLevel = levels[curLevel->getId() + 1].get();
	}
}

void Model::levelDown(){
	if (curLevel->getId() == 0){
		throw QuadrisException{"The current level is already the lowest level"};
	}
	else{
		curLevel = levels[curLevel->getId() - 1].get();
	}
}

void Model::preMovement(){
	board.clear(*undroppedBlock);
}

void Model::postMovement(){
	board.add(*undroppedBlock, undroppedBlock->getType());
}

void Model::updateBlocksAndScore(const list<size_t> &completedRowsId)
{
	if (completedRowsId.size() > 0){
		
		// add score for clearing lines
		unsigned int base = curLevel->getId() + completedRowsId.size();
		addScore(base * base);
		
		clearRows(completedRowsId);
		moveUpperBlocks(completedRowsId);
		board.update(droppedBlocks);
	}
}

void Model::dropBlock()
{
	if (!gameover){

		preMovement();
		undroppedBlock->drop(*this);
		postMovement();
	
		// add the previously undropped block into blocks
		droppedBlocks.emplace_back(move(undroppedBlock));
	
		// check if any lines has been completed
		const list<size_t> completedRowsId = board.getCompletedRowsId();
		updateBlocksAndScore(completedRowsId);

		// if current level is 4, then we may need to add asterisk block at the center
		Level4 *level_ptr = dynamic_cast<Level4*>(curLevel);
		if (level_ptr){
			// only increment this when the game is in level 4
			++numAccumulatedBlocks;
			// if this drop clears any row, reset the accumulated number of dropped blocks 
			if (completedRowsId.size() > 0) numAccumulatedBlocks = 0;
			// only if no lines are cleared in this drop may we need an obstace
			// so we can use an else if
			else if (numAccumulatedBlocks == Level4::threshold){
	
				// entering this block means that we need to drop an obstacle
	
				// reset first
				numAccumulatedBlocks = 0; 
	
				// create the obstacle at the top of center column and drop it
				unique_ptr<Block> asterisk = level_ptr->createBlock(Block::asteriskType);
				asterisk->drop(*this);

				if (board.isValid(*asterisk)){

					board.add(*asterisk, asterisk->getType());
					droppedBlocks.emplace_back(move(asterisk));

					// Maybe there is a line completed by the obstacle by chance
					const list<size_t> completedRowsId = board.getCompletedRowsId();
					updateBlocksAndScore(completedRowsId);
				}
				// if there is no space for the obstacle
				else {
					// move it up by one cell, which makes valid on the board
					asterisk->up(*this);
					// add it to the board to let the user know why the game is over
					board.add(*asterisk, asterisk->getType());

					gameover = true;	
				}
				
			}
		}
	
		// undropped block is now the previously next block
		undroppedBlock.swap(nextBlock);
		// nextBlock now contains the previously undropped block,
		// which will be deallocated when we reset nextBlock
	
		// now we need to generate next block
	
		// randomness only matters in level 3 and 4
		if (!random && curLevel->getId() >= 3){
	
			// there should be something for us to generate
			assert (noRandomSequence.size() > 0);
	
			// take the element first, then increment the index
			char type = noRandomSequence[curIdForNRS++];
			// move assignment -> release the previous undropped block
			nextBlock = curLevel->createBlock(type);
	
			// if we have used up the noRandomSequence, then reuse it from the beginning
			if (curIdForNRS == noRandomSequence.size()) curIdForNRS = 0;
		}
		else{
			// move assignment -> release the previous undropped block
			nextBlock = curLevel->createBlock();
		}
	
		// if the current undropped block is invalid at its initial position
		// then game is over
		if (!board.isValid(*undroppedBlock)) gameover = true;
			
		// if game is over
		// then move the current undropped block up enough to avoid overlapping other existing blocks
		// to display it on UI in order to let the user know why the game is over
		if (gameover){
			while (!undroppedBlock->up(*this));
		}
	
		// whether the game is over,
		// the undropped block is now valid on the board
		board.add(*undroppedBlock, undroppedBlock->getType());
	}
	else throw QuadrisException{"You can't drop block when game is over"};
}

void Model::setNoRandomSequence(std::vector<char> &&sequence){
	random = false;
	noRandomSequence = sequence;	
	// reset index
	curIdForNRS = 0;
}

void Model::restoreRandomness(){
	random = true;
}

void Model::restartGame(){
	droppedBlocks.clear();
	board.update(droppedBlocks);
	clearHint();
	noRandomSequence.clear();
	reset();
}

unique_ptr<Block> Model::findHint()
{
	unique_ptr<Block> res;

	// make a clone of undropped block
	unique_ptr<Block> tmp = undroppedBlock->clone();
	
	//move the undropped block as left as it can
	while(tmp->left(*this));

	// initialize maxReward to be worse than all the possible rewards
	unsigned int unreachableCellsIncreased = Board::numGameRows * Board::numCols;
	Reward maxReward{0, unreachableCellsIncreased, 0};

	// get the current statistics first
	unsigned int numUnreachableCells = board.numUnreachableCells();

	// because for each block, by rotating it by at most 4 times,
	// it will either pass through or restore the original state
	// that is, we can exhaust all the possibilities
	const int maxRotateNum = 4;

	for(int i = 0; i < maxRotateNum; ++i){
		
		unique_ptr<Block> tmp1 = tmp->clone();
		
		while(true){
			
			// make a clone of the possible hint block before dropping it
			unique_ptr<Block> curHintBlock = tmp1->clone();

			curHintBlock->drop(*this);
			// place this possible hint block to the board
			board.add(*curHintBlock, undroppedBlock->getType()); 
			
			// calculate the reward of current hint
			unsigned int rowsErased = board.getCompletedRowsId().size();
			unsigned int unreachableCellsIncreased = board.numUnreachableCells() - numUnreachableCells;
			unsigned int highestCellPos = curHintBlock->getBoundingBox().getY();
			Reward curReward{rowsErased, unreachableCellsIncreased, highestCellPos};
			
			// remove current hint block from the board
			board.clear(*curHintBlock);

			if(curReward > maxReward){ 
				res = move(curHintBlock);
				maxReward = curReward;
			}

			// move the hint block right
			if(!tmp1->right(*this)) break;
		}

		// end for right movement
		// rotate the clone of the original undropped block
		if (!tmp->c_rotate(*this)) break;
	}

	return res;
}

void Model::showHint()
{
	if (!gameover){

		// hint block should contains nothing at this moment
		assert (!hintBlock);
	
		// to avoid clash when deciding where the hint block should be
		board.clear(*undroppedBlock);
	
		hintBlock = findHint();
	
		board.add(*hintBlock, Block::hintType);
		// undropped block may cover part of hint block
		board.add(*undroppedBlock, undroppedBlock->getType());
	}
}

void Model::clearHint(){

	// if there is indeed a hint block on the board now
	if (hintBlock){

		// maybe hint block overlaps part of undropped block,
		// then that part of undropped block will be cleared as well
		board.clear(*hintBlock);
		// so we need to add undropped block to board again just in case
		board.add(*undroppedBlock, undroppedBlock->getType());

		// deallocate previously allocated memory in hint block and set it to nullptr
		hintBlock.reset(nullptr);
	}
}
