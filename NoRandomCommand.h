#ifndef NORANDOM_COMMAND_H
#define NORANDOM_COMMAND_H

#include "Command.h"
#include <string>

class NorandomCommand : public Command{
public:
	void execute(Model &model,const std::string &args) const override;	
};
#endif
