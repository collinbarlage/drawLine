#include <vector>
#include <string>
#include "Framebuffer.h"
#include "Shapebuffer.h"
#include "Polygon.h"
#include "Line.h"
#ifndef _PS_
#define _PS_
using namespace std;
class Framebuffer;

class Ps
{
public:
	//constructors
	Ps(void);

	//destructor
	~Ps(void);

	//Methods
	void input(string input);
	void makeFramebuffer(bool dda);
	char getPixel(int x, int y);
	
	//public vars
	float scale;
	int rotation;
	int xTrans;
	int yTrans;
	int xWorldMin;
	int yWorldMin;
	int xWorldMax;
	int yWorldMax;
	int xViewMin;
	int yViewMin;
	int xViewMax;
	int yViewMax;



private:
	Framebuffer fb;
	Polygon& getPolygon();
	vector<Line> lines;
	vector<Line> validLines;
	vector<Polygon> polygons;
	void addLine(Line *l);
	void addValidLine(Line *l);
	void addPolygon(Polygon *p);
};
#endif