#include "Point.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

Point::Point(void)
{
}


Point::Point(int X, int Y) {
	x = X;
	y = Y;
	bitcode[0] = 1;
	bitcode[1] = 1;
	bitcode[2] = 1;
	bitcode[3] = 1;
}

Point::Point(float X, float Y) {
	x = round(X);
	y = round(Y);
	bitcode[0] = 1;
	bitcode[1] = 1;
	bitcode[2] = 1;
	bitcode[3] = 1;
}

Point::~Point(void)
{
}

void Point::setBitcode(int xMax, int yMax) {
	//set bit codes
	y > yMax? bitcode[0] = 1 : bitcode[0] = 0; //above
	y < 0?    bitcode[1] = 1 : bitcode[1] = 0;  //below
	x > xMax? bitcode[2] = 1 : bitcode[2] = 0; //right 
	x < 0?    bitcode[3] = 1 : bitcode[3] = 0;  //left
}

void Point::clip(int xMax, int yMax, Point o, float slope) {
	//reset bitcodes
	setBitcode(xMax, yMax);
	cout <<  "bitcode =  "<< bitcode[0] << bitcode[1] << bitcode[2] << bitcode[3] << endl; 

	if(bitcode[0] == 1) { //point is above
		y = yMax;
		x = o.getX() + float(y - o.getY())/slope;
		//cout << " o.getX() + float(y - o.getY())/slope\n";
		//cout << o.getX() << " + float(" << y << " - " <<o.getY()<<") / " << slope <<endl;
		cout << "point above ---> "<< x << " "<< y << endl; 
		return;
	}
	if(bitcode[1] == 1) { //point is below
		y = 0;
		x = o.getX() + round(float(0 - o.getY())/slope);
	cout << "point below ---> "<< x << " "<< y << endl; 
		return;
	}
	if(bitcode[2] == 1) { //point is right
		x = xMax;
		y = round(float((slope * (x - o.getX())) + o.getY()));
		cout << "point right ---> "<< x << " "<< y << endl; 

		return;
	}
	if(bitcode[3] == 1) { //point is left
		x = 0;
		if(y > o.getY()) {
			slope = abs(slope);
		}
		y = round(float((slope * abs(o.getX())) + o.getY()));
		cout << "point left ---> "<< x << " "<< y << endl; 
		return;
	}


}

bool Point::isOutOfBounds() {
	//check to see if bitcode == 1
	for(int i=0; i<4; i++) {
		if(bitcode[i] == 1) {
			return true;
		}
	}
	return false;
}


int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

void Point::setX(int n) {
	x = n;
}

void Point::setY(int n) {
	y = n;
}

void Point::swap(Point &p) {
	int tempX = p.getX();
	int tempY = p.getY();
	p.setX(x);
	p.setY(y);
	x = tempX;
	y = tempY;

}


bool Point::equals(Point p) {
	if(x == p.getX() && y == p.getY()) {
		return true;
	}
	return false;
}

int Point::logicAnd(int bits[4]) {
	for(int i=0; i<4; i++) {
		if(bits[i] == 1 && bitcode[i] == 1) {
			return 1;
		}
	}
	return 0;
}

int Point::round(float n) {
	float diff = n - int(n);
	if(diff < .5) {
		return int(n);
	} else {
		return int(n) + 1;
	}
}