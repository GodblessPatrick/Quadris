#ifndef LCOMMAND_H
#define LCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class LCommand : public ReplaceCommand {
	void execute(Model &model, const std::string &args) const override; 
};
#endif
  
