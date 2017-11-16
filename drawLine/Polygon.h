#ifndef _POLYGON_
#define _POLYGON_
#include <string>
#include <vector>
#include "Point.h"
#include "Shapebuffer.h"

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
	void draw(Shapebuffer &sb);
	void addPoint(string x, string y);
	void addPoint(const Point *p);
	Point getPoint(int i);
	void replacePoint(int i, Point p);
	void finishPolygon();
	void rotate(int theta);
	void scale(float sx, float sy);
	void trans(int dx, int dy);
	bool isValid();
	int  size();

private:
	vector<Point> points;
	bool valid; 
	void checkCorners(int side, int inOut);
	int corners[4];
};
#endif
