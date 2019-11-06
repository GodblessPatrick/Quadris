#ifndef CLOCKWISE_COMMAND_H
#define CLOCKWISE_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class ClockwiseCommand : public MoveCommand{
	public:
		void execute(Model &model,const std::string &args) const override;
};
#endif
