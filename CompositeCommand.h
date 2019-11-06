#ifndef COMPOSITE_COMMAND_H
#define COMPOSITE_COMMAND_H

#include <list>
#include <string>
#include "Command.h"
class Model;

class CompositeCommand : public Command{
	std::list<const Command*> commands;
public:
	void execute(Model &model, const std::string &args) const override;
	void add(const Command *command);
};

#endif

