#include <string>
#ifndef _POINT_
#define _POINT_
using namespace std;

class Point
{
public:
	//constructors
	Point(void);
	Point(int x, int y);
	Point(float x, float y);

	//destructor
	~Point(void);

	//methods
	void clip(int x, int y, Point o, float slope);
	int getX() const;
	int getY() const;
	int getW() const;
	void setX(int n);
	void setY(int n);
	void setW(int n);
	void rotate(int theta);
	void scale(float sx, float sy);
	void trans(int dx, int dy);
	bool isOutOfBounds();
	int bitcode[4];
	void setBitcode(int x, int y);
	int logicAnd(int bits[4]); //logical AND on bitcodes
	void swap(Point &p);
	bool equals(Point p);

private:
	int x;
	int y;
	int w; //homogenous coordinate
	int round(float n);

};
#endif
