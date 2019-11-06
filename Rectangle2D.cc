#include "Rectangle2D.h"

void Rectangle2D::reset(int x, int y, int w, int h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

int Rectangle2D::getX() const
{
	return x;	
}

int Rectangle2D::getY() const
{
	return y;
}

int Rectangle2D::getW() const
{
	return w;
}

int Rectangle2D::getH() const
{
	return h;
}

