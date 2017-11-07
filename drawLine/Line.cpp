#include "Line.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

Line::Line(void)
{
	valid = true;
}


Line::Line(string x1, string y1, string x2, string y2) {
	//assign points
	p1 = Point(stoi(x1), stoi(y1));
	p2 = Point(stoi(x2), stoi(y2));
	p1.setBitcode(499, 499);
	p2.setBitcode(499, 499);

	slope = float(p2.getY() - p1.getY()) / float(p2.getX() - p1.getX());

	//logical AND bitcodes to see if we should draw anything
	if(p1.logicAnd(p2.bitcode) == 1) { //lines are totally outside of clipping area!
		valid = false;
	} else {
		valid = true;
	}
}

Line::Line(Point point1, Point point2, Framebuffer &fb) {
	//assign points
	p1 = point1;
	p2 = point2; 
	p1.setBitcode(fb.x, fb.y);
	p2.setBitcode(fb.x, fb.y);

	slope = float(p2.getY() - p1.getY()) / float(p2.getX() - p1.getX());

	//logical AND bitcodes to see if we should draw anything
	if(p1.logicAnd(p2.bitcode) == 1) { //lines are totally outside of clipping area!
		valid = false;
	} else {
		valid = true;
	}
}

Line::~Line(void)
{
}

void Line::draw(Framebuffer &fb) {
	cout << "drawing line: (" << p1.getX() << ", " << p1.getY() << ") -> (" << p2.getX() << ", " << p2.getY() << ")\n";

	//check bounderys for clipping
	if(isNotInBounds(fb.x, fb.y != 0)) {
		clip(fb.x, fb.y); //clip!
	}

	//assign points
	int x1, x2, y1, y2;
	if(p1.getX() > p2.getX()) {
		//swap negitive quadrent
		x2 = p1.getX(); y2 = p1.getY();
		x1 = p2.getX(); y1 = p2.getY();
	} else {
		x1 = p1.getX(); y1 = p1.getY();
		x2 = p2.getX(); y2 = p2.getY();
	}

	if(valid){ //Draw DDA
		float x = float(x1); //initial X starting point
		float y = float(y1); //initial Y starting point

		if( slope < -1) {
			//decrement y
			while(y > y2) {
				fb.setPixel(x, y, '#'); 
				x = x - 1/slope;
				y--;
			}
		} else if(slope < 1) {
			//increment x
			while(x < x2) {
				fb.setPixel(x, y, '#'); 
				y = y + slope;
				x++;
			}
		} else {
			//increment y
			while(y < y2) {
				fb.setPixel(x, y, '#'); 
				x = x + 1/slope;
				y++;
			}
		}
		//don't forget about last point!
		fb.setPixel(x, y, '#'); 
	}

}

Point Line::getClipPoint1(Framebuffer &fb) {
	while(p1.isOutOfBounds()) {
		p1.clip(fb.x, fb.y, p1, slope);
	}
	return p1;
}
Point Line::getClipPoint2(Framebuffer &fb) {
	while(p2.isOutOfBounds()) {
		p2.clip(fb.x, fb.y, p1, slope);
	}
	return p2;
}


int Line::isNotInBounds(int xMax, int yMax) {
	if(p1.isOutOfBounds() && p2.isOutOfBounds()) { 
		//cout << " out -> out \n";
		return 3;

	} // 2 = out -> in
	else if(p1.isOutOfBounds() && !p2.isOutOfBounds()) {
		//cout << " out -> in \n";
		return 2;

	}// 1 = in -> out
	else if(!p1.isOutOfBounds() && p2.isOutOfBounds()) {
		//cout << " in -> out \n";
		return 1;
	} // 0 = inbounds
	else { // 0 = inbounds
		//cout << " in -> in \n";
		return 0;
	}
}

void Line::clip(int xMax, int yMax) {
	cout << "slope = " << slope << endl;
	//first, set bitcodes
	p1.setBitcode(xMax, yMax);
	p2.setBitcode(xMax, yMax);

	if(!valid) {
		return;
	}

	//clip points
	while(p1.isOutOfBounds()) {
		p1.clip(xMax, yMax, p1, slope);
	}
	while(p2.isOutOfBounds()) {
		p2.clip(xMax, yMax, p1, slope);
	}

}

Point Line::getPoint(int n) {
	if(n == 1) {
		return p1;
	} else {
		return p2;
	}
}

int Line::getX1() {
	return p1.getX();
}

int Line::getX2() {
	return p2.getX();
}
int Line::getY1() {
	return p1.getY();
}
int Line::getY2() {
	return p2.getY();
}

bool Line::isValid() {
	return valid;
}
