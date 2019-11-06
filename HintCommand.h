#ifndef HINT_COMMAND_H
#define HINT_COMMNAD_H

#include "Command.h"
#include <string>

class HintCommand : public Command{
public:
	void execute(Model &model,const std::string &args) const override;
};
#endif
