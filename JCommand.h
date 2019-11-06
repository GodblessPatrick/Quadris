#ifndef JCOMMAND_H
#define JCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class JCommand : public ReplaceCommand {
public:
	void execute(Model &model, const std::string &args) const override; 
};
#endif
