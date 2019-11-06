#ifndef ZCOMMAND_H
#define ZCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class ZCommand : public ReplaceCommand {
	void execute(Model &model, const std::string &args) const override; 
};
#endif
  
