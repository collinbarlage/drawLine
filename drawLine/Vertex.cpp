#include "Vertex.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

Vertex::Vertex(void)
{
}


Vertex::Vertex(float X, float Y, float Z) {
	x = X;
	y = Y;
	z = Z;
	w = 1;
}

Vertex::~Vertex(void)
{
}


float Vertex::getX() const {
	return x;
}

float Vertex::getY() const {
	return y;
}

float Vertex::getZ() const {
	return z;
}

int Vertex::getW() const {
	return w;
}

void Vertex::setX(float n) {
	x = n;
}

void Vertex::setY(float n) {
	y = n;
}

void Vertex::setZ(float n) {
	z = n;
}

void Vertex::setW(int n) {
	w = n;
}

bool Vertex::equals(Vertex v) {
	if(x == v.getX() && y == v.getY() && z == v.getZ()) {
		return true;
	}
	return false;
}

void Vertex::multiply(Matrix m) {
	float col[4];
	float v[4] = {w,z,y,x};
	for(int j=3; j>=0; j--) {
		col[j] = m.get(0,j)*v[j] + m.get(1,j)*v[j] + m.get(2,j)*v[j] + m.get(3,j)*v[j] ;
	}
	x = col[3];
	y = col[2];
	z = col[1];
	w = col[0];
	
}
