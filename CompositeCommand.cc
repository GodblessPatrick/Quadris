#include "CompositeCommand.h"
#include "QuadrisException.h"
#include "Model.h"
#include <string>

using namespace std;

void CompositeCommand::execute(Model &model, const string &args) const
{
	string err_msg;
	for (const auto &command : commands){
		try { command->execute(model, args); }
		catch (const QuadrisException &ex) {
			if (err_msg != "") err_msg += '\n';
			err_msg += ex.what();
		}
	}
	if (err_msg != "") throw QuadrisException{err_msg};
}

void CompositeCommand::add(const Command *command){
	commands.push_back(command);
}
