#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <map>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	Pixmap pix;
	int width, height;
	std::map<std::string, unsigned long> colors;
 public:
	Xwindow(int width, int height, const std::vector<std::string> &colorNames);  // Constructor; displays the window.
	~Xwindow();                              // Destructor; destroys the window.
	Xwindow(const Xwindow&) = delete;
	Xwindow &operator=(const Xwindow&) = delete;

	void drawString(int x, int y, std::string msg);
	void drawLine(int x1, int y1, int x2, int y2);
	void fillRectangle(int x, int y, int width, int height, const std::string &colorName);

	void flush();
};

#endif
