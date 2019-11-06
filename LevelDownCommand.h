#ifndef LEVELDOWN_COMMAND_H
#define LEVELDOWN_COMMAND_H
#include "Command.h"
class Model;

class LevelDownCommand : public Command {
  void execute(Model &model, const std::string &args) const override;
};

#endif
