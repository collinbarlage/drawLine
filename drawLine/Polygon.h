#ifndef _POLYGON_
#define _POLYGON_
#include <string>
#include <vector>
#include "Point.h"
#include "Framebuffer.h"

using namespace std;

class Polygon
{
public:
	//constructors
	Polygon(void);
	Polygon(string x, string y);
	 

	//destructor
	~Polygon(void);

	//methods
	void draw(Framebuffer &fb);
	void addPoint(string x, string y);
	void addPoint(const Point *p);
	Point getPoint(int i);
	void replacePoint(int i, Point p);
	void finishPolygon();
	bool isValid();
	int  size();

private:
	vector<Point> points;
	bool valid; 
};
#endif
