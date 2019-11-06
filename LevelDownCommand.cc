#include "LevelDownCommand.h"
#include "Model.h"
#include <string>
using namespace std;

void LevelDownCommand::execute(Model &model, const std::string &args) const {
  model.levelDown();
}
