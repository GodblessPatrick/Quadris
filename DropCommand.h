#ifndef DROP_COMMAND_H
#define DROP_COMMAND_H

#include "MoveCommand.h"
#include <string>
class Model;

class DropCommand : public Command {
public:
	void execute(Model &model, const std::string &args) const override;
};

#endif

