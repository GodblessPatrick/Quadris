#include "Cell.h"

Cell::Cell(int x, int y) : x{x}, y{y}
{
	visible = true;
}

int Cell::getX() const
{
	return x;
}

int Cell::getY() const
{
	return y;
}

bool Cell::isVisible() const
{
	return visible;		
}

void Cell::disappear(){
	visible = false;	
}

