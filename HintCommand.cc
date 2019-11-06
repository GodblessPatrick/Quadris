#include "Model.h"
#include "HintCommand.h"
#include <string>
using namespace std;

void HintCommand::execute(Model &model,const string &args) const
{
	model.showHint();
}
