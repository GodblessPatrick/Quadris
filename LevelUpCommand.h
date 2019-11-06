#ifndef LEVELUP_COMMAND_H
#define LEVELUP_COMMAND_H
#include "Command.h"
class Model;

class LevelUpCommand : public Command {
  void execute(Model &model, const std::string &args) const override;
};

#endif
