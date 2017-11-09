#include <string>
#include "Framebuffer.h"
#include "Polygon.h"
#include "Line.h"
#ifndef _SHAPEBUFFER_
#define _SHAPEBUFFER_
using namespace std;

class Framebuffer; class Polygon;

class Shapebuffer
{
public:
	Shapebuffer(void);

	~Shapebuffer(void);

	//Methods
	void draw(Framebuffer &fb);
	void fill(Polygon p, char c);
	char getPixel(int x, int y);
	void setPixel(int x, int y, char pixel);
	void setPixel(float x, float y, char pixel);


	//vars
	int height;
	int width;
	int x;
	int y;

private:
	char canvas[500][500]; //default: 500px by 500px size
	int round(float n);
	bool isTopVertex(int x, int y, Polygon p);
	bool isYMax(Point a, Point b, Point c);
	bool isRightTriangle(Point a, Point b, Point c);
	bool isHorizontal(Point a, Point b);
};

#endif