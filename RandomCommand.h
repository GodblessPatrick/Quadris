#ifndef RANDOM_COMMAND_H
#define RANDOM_COMMNAD_H

#include "Command.h"
#include <string>

class RandomCommand : public Command{
public:
	void execute(Model &model,const std::string &args) const override;
};
#endif
