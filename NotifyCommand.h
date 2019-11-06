#ifndef NOTIFY_COMMAND_H
#define NOTIFY_COMMAND_H

#include "Command.h"
#include <string>
class Model;

class NotifyCommand : public Command {
public:
	void execute(Model &model, const std::string &args) const override;	
};

#endif
