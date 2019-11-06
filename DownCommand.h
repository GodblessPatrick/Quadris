#ifndef DOWN_COMMAND_H
#define DOWN_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class DownCommand : public MoveCommand{
	public:
		void execute(Model &model,const std::string &args) const override;
};
#endif
