#include <string>
#include "Matrix.h"
#ifndef _VERTEX_
#define _VERTEX_
using namespace std;
class Matrix;

class Vertex
{
public:
	//constructors
	Vertex(void);
	Vertex(float x, float y, float z);

	//destructor
	~Vertex(void);

	//methods
	float getX() const;
	float getY() const;
	float getZ() const;
	int getW() const;
	void setX(float n);
	void setY(float n);
	void setZ(float n);
	void setW(int n);
	bool isOutOfBounds();
	bool equals(Vertex v);
	void rotate();
	void multiply(Matrix m);


private:
	float x;
	float y;
	float z;
	int w; //homogenous coordinate

};
#endif
