#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "Command.h"
class Model;

class MoveCommand : public Command{
protected:
	void preMovement(Model &model) const;
	void postMovement(Model &model) const;
};

#endif
