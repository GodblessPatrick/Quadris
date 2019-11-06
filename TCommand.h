#ifndef TCOMMAND_H
#define TCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class TCommand : public ReplaceCommand {
	void execute(Model &model, const std::string &args) const override;
};
#endif
  
