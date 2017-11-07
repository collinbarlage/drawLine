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
	void setX(int n);
	void setY(int n);
	bool isOutOfBounds();
	int bitcode[4];
	void setBitcode(int x, int y);
	int logicAnd(int bits[4]); //logical AND on bitcodes
	void swap(Point &p);
	bool equals(Point p);

private:
	int x;
	int y;
	int round(float n);

};
#endif
