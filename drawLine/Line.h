#pragma once
#ifndef _LINE_
#define _LINE_
#include <string>
#include "Framebuffer.h"
#include "Point.h"
using namespace std;

class Framebuffer;

class Line
{
public:
	//constructors
	Line(void);
	Line(string x1, string y1, string x2, string y2);
	Line(Point p1, Point p2, Framebuffer &fb);

	//destructor
	~Line(void);

	//methods
	void draw(Framebuffer &fb);
	void clip(int x, int y);
	bool isValid();
	int  isNotInBounds(int xMax, int yMax);
	Point getPoint(int n);
	Point getClipPoint(Framebuffer &fb);
	int getX1();
	int getX2();
	int getY1();
	float slope;
	int getY2();

private:
	Point p1;
	Point p2;
	bool valid; 
};
#endif
