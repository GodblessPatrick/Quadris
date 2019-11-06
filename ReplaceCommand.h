#ifndef REPLACE_COMMAND_H
#define REPLACE_COMMAND_H

#include "Command.h"
class Block;
class Cell;

class ReplaceCommand : public Command {
protected:
	static Cell findOffset(const Block &block);
};

#endif
