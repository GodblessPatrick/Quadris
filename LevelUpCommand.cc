#include "LevelUpCommand.h"
#include "Model.h"
#include <string>
using namespace std;

void LevelUpCommand::execute(Model &model, const std::string &args) const {
  model.levelUp();
}
