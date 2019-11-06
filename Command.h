#ifndef COMMAND_H
#define COMMAND_H

#include <string>
class Model;

class Command {
public:
	virtual void execute(Model &model, const std::string &args) const = 0;
	virtual ~Command();
};

#endif
