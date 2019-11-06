#include "ClockwiseCommand.h"
#include "QuadrisException.h"
#include "Model.h"
#include <string>
#include <utility>  // move

using namespace std;

void ClockwiseCommand::execute(Model &model,const string &args) const
{
	model.preMovement();
	Block &undropblock = model.getUndroppedBlock();
	bool success = undropblock.c_rotate(model);
	model.postMovement();
	if (!success){
		string message = "The undropped block can't be rorated clockwise at this position";
		throw QuadrisException{move(message)};
	}
}
