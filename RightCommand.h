#ifndef RIGHT_COMMAND_H
#define RIGHT_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class RightCommand : public MoveCommand{
	public:
		void execute(Model &model,const std::string &args) const override;
};
#endif
