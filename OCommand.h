#ifndef OCOMMAND_H
#define OCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class OCommand : public ReplaceCommand {
public:
	void execute(Model &model, const std::string &args) const override; 
};
#endif
