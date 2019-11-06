#ifndef COUNTERCLOCKWISE_COMMAND_H
#define COUNTERCLOCKWISE_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class CounterClockwiseCommand : public MoveCommand{
	public:
		void execute(Model &model,const std::string &args) const override;
};
#endif
