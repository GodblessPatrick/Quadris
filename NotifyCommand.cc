#include "NotifyCommand.h"
#include "Model.h"
#include <string>
#include <iostream>
using namespace std;

void NotifyCommand::execute(Model &model, const string &args) const
{
	model.notifyObservers();
}

