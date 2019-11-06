#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

class Rectangle2D {
	int x, y, w, h;	
public:
	void reset(int x, int y, int w, int h);
	int getX() const;
	int getY() const;
	int getW() const;
	int getH() const;
};

#endif
