#ifndef LEFT_COMMAND_H
#define LEFT_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class LeftCommand : public MoveCommand{
	public:
		void execute(Model &model,const std::string &args) const override;
};
#endif
