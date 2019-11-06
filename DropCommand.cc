#include "DropCommand.h"
#include "Model.h"
#include <string>

using namespace std;

void DropCommand::execute(Model &model, const string &args) const
{
	model.dropBlock();
}

