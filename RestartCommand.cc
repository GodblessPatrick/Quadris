#include "Model.h"
#include "RestartCommand.h"
#include <string>
using namespace std;

void RestartCommand::execute(Model &model,const string &args) const
{
	model.restartGame();
}

