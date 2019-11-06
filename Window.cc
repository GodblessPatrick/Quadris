#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <vector>
#include "Window.h"

using namespace std;

Xwindow::Xwindow(int width, int height, const vector<string> &colorNames) : width{width}, height{height}
{
	d = XOpenDisplay(NULL);
	if (d == NULL) {
	  cerr << "Cannot open display" << endl;
	  exit(1);
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 1, 1, width, height, 1,
	                        BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapRaised(d, w);

	pix = XCreatePixmap(d,w,width,
	      height,DefaultDepth(d,DefaultScreen(d)));
	gc = XCreateGC(d, pix, 0,(XGCValues *)0);

	XFlush(d);
	XFlush(d);

	// Set up colours.
	XColor color;
	Colormap cmap;

	cmap = DefaultColormap(d,DefaultScreen(d));
	for(const string &colorName : colorNames) {
	    XParseColor(d, cmap, colorName.c_str(), &color);
	    XAllocColor(d, cmap, &color);
	    colors[colorName] = color.pixel;
	}

	XSetForeground(d,gc,colors["Black"]);

	// Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	XSynchronize(d,True);

	usleep(1000);
}

void Xwindow::drawString(int x, int y, string msg) {
	XDrawString(d, pix, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawLine(int x1, int y1, int x2, int y2){
	XDrawLine(d, pix, DefaultGC(d, s), x1, y1, x2, y2);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, const string &colorName) {
	XSetForeground(d, gc, colors[colorName]);
	XFillRectangle(d, pix, gc, x, y, width, height);
}

void Xwindow::flush() {
	XCopyArea(d, pix, w, gc, 0, 0, width, height, 0, 0);
	XFlush(d);
}

Xwindow::~Xwindow() {
	XFreeGC(d, gc);
	XCloseDisplay(d);
}
