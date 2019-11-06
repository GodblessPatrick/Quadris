#ifndef RESTART_COMMAND_H
#define RESTART_COMMNAD_H

#include "Command.h"
#include <string>

class RestartCommand : public Command{
public:
	void execute(Model &model,const std::string &args) const override;
};
#endif

