#include "Model.h"
#include "RandomCommand.h"
#include <string>
using namespace std;

void RandomCommand::execute(Model &model,const string &args) const
{
	model.restoreRandomness();
}
