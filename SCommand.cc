#include "SCommand.h"
#include "Model.h"
#include "BlockFactory.h"
#include "Cell.h"
#include <string>
using namespace std;

void SCommand::execute(Model &model, const string &args) const
{
	Cell upperLeftCell = ReplaceCommand::findOffset(model.getUndroppedBlock());
	int tx = upperLeftCell.getX(), ty = upperLeftCell.getY();
	model.setUndroppedBlock(BlockFactory::createBlock('S', model.getUndroppedBlock().getLevelId(), tx, ty));
}
