#include "RightCommand.h"
#include "QuadrisException.h"
#include "Model.h"
#include <string>
#include <utility>  // move

using namespace std;

void RightCommand::execute(Model &model,const string &args) const
{
	model.preMovement();
	Block &undropblock = model.getUndroppedBlock();
	bool success = undropblock.right(model);
	model.postMovement();
	if (!success){
		string message = "The undropped block can't be moved right at this position";
		throw QuadrisException{move(message)};
	}
}
