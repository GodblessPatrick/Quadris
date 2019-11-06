#include "CounterClockwiseCommand.h"
#include "QuadrisException.h"
#include "Model.h"
#include <string>
#include <utility>  // move

using namespace std;

void CounterClockwiseCommand::execute(Model &model,const string &args) const
{
	model.preMovement();
	Block &undropblock = model.getUndroppedBlock();
	bool success = undropblock.cc_rotate(model);
	model.postMovement();
	if (!success){
		string message = "The undropped block can't be rorated counterclockwise at this position";
		throw QuadrisException{move(message)};
	}
}
