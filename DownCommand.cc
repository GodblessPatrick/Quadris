#include "DownCommand.h"
#include "QuadrisException.h"
#include "Model.h"
#include <string>
#include <utility>  // move

using namespace std;

void DownCommand::execute(Model &model,const string &args) const
{
	model.preMovement();
	Block &undropblock = model.getUndroppedBlock();
	bool success = undropblock.down(model);
	model.postMovement();
	if (!success){
		string message = "The undropped block can't be moved down at this position";
		throw QuadrisException{move(message)};
	}
}
