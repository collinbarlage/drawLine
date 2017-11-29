#ifndef _MATRIX_
#define _MATRIX_
#include <iostream>
using namespace std;

class Matrix
{
public:
	Matrix(void);
	Matrix(float a, float b, float c, float w);
	~Matrix(void);
	Matrix cross(Matrix m);
	Matrix multiply(Matrix m);
	float get(int i, int j);
	void  set(int i, int j, float f);
	void  addColumn(float a, float b, float c, float d);
	void  print();

private:
	float v[4][4];
	int n;
};

#endif
