#include "ReplaceCommand.h"
#include "Block.h"
#include "Rectangle2D.h"
#include "Cell.h"

Cell ReplaceCommand::findOffset(const Block &block){
	const Rectangle2D &boundingBox = block.getBoundingBox();
	// the upper-left corner of the bounding box
	return Cell{boundingBox.getX(), boundingBox.getY()};
}
