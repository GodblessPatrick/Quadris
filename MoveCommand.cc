#include "MoveCommand.h"
#include "Model.h"

void MoveCommand::preMovement(Model &model) const
{
	model.preMovement();
}

void MoveCommand::postMovement(Model &model) const
{
	model.postMovement();
}

