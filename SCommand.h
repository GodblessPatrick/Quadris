#ifndef SCOMMAND_H
#define SCOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class SCommand : public ReplaceCommand {
public:
	void execute(Model &model, const std::string &args) const override; 
};
#endif
