#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "ReplaceCommand.h"
#include <string>

class ICommand : public ReplaceCommand {
public:
	void execute(Model &model, const std::string &args) const override;
};
#endif
