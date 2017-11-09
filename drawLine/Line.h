#pragma once
#ifndef _LINE_
#define _LINE_
#include <string>
#include "Shapebuffer.h"
#include "Point.h"
using namespace std;

class Shapebuffer;

class Line
{
public:
	//constructors
	Line(void);
	Line(string x1, string y1, string x2, string y2);
	Line(Point p1, Point p2, Shapebuffer &sb);

	//destructor
	~Line(void);

	//methods
	void draw(Shapebuffer &sb);
	void clip(int x, int y);
	bool isValid();
	int  isNotInBounds(int xMax, int yMax);
	Point getPoint(int n);
	Point getClipPoint1(Shapebuffer &sb);
	Point getClipPoint2(Shapebuffer &sb);
	int getX1();
	int getX2();
	int getY1();
	int getY2();
	float slope;

private:
	Point p1;
	Point p2;
	int x1, x2, y1, y2;
	bool valid; 
};
#endif
