#include "Shapebuffer.h"
#include <iostream>
#include <fstream>

Shapebuffer::Shapebuffer(void)
{
	width = sizeof canvas[0] / sizeof(char); 
	height =  sizeof canvas / sizeof canvas[0];  
	x = width  - 1;
	y = height - 1;

	//make canvas white?
	for(int j=0; j<height; j++){
		for(int i=0; i<width; i++){
			canvas[i][j] = '-';
		}
	}
}


Shapebuffer::~Shapebuffer(void)
{
}

void Shapebuffer::draw(Framebuffer &fb) {
	char pixel;
	for(int j=0; j<fb.height; j++) {
		for(int i=0; i<fb.width; i++) {
			pixel = getPixel(i,j);
			if(pixel == '#') {
				fb.setPixel(i, j, pixel);
			}
		}
	}
}

void Shapebuffer::fill(Polygon p, char c) {
	int flag;

	for(int j=0; j<height; j++) {
		flag = 0;
		for(int i=0; i<width; i++) {
			//check if intersecting with a line
			if(getPixel(i,j) == c) {
				if(isTopVertex(i,j,p) && getPixel(i+1,j) == '-') {
					//ignore
					cout << endl;
				} else if(isTopVertex(i,j,p) && getPixel(i+1,j) == c) {
					//ignore multiple
					while(getPixel(i+1,j) == c) {
						//cout << "ignored a pixel.." << endl;
						i++;
						if(isTopVertex(i,j,p)) {
							break;
						}
					}
					cout << endl;
				} else if(getPixel(i+1,j) == c) {
					//ignore thick line
				} else {
					flag++;
				}
			}

			//fill if flag is odd
			if(flag % 2 == 1) {
				setPixel(i,j, c);
			}
		}
	}
}

bool Shapebuffer::isTopVertex(int x, int y, Polygon p) {
	for(int i=0; i<p.size()-1; i++) {
		if(p.getPoint(i).getX() == x && p.getPoint(i).getY() == y) {
			//get 2 points surrounding current point 'b'
			Point a, b, c;
			b = p.getPoint(i);
			c = p.getPoint(i+1);
			if(i == 0) {
				a = p.getPoint(p.size()-2);
			} else {
				a = p.getPoint(i-1);
			}


			if((b.getY() >= a.getY() && b.getY() >= c.getY()) ||
				(b.getY() <= a.getY() && b.getY() <= c.getY())) {
					//cout << "[" << a.getX() << "][" << a.getY() << "] -> [" << b.getX() << "][" << b.getY() << "] -> ["  << c.getX() << "][" << c.getY() << "]";
					cout << "TOP";
					return true;
			} else if( isYMax(a,b,c) && isRightTriangle(a,b,c)) {
				cout << "Corner!";
				return true;

			} else {
				cout << "mid";
				return false;
			}
		}
	}
	return false;
}

bool Shapebuffer::isHorizontal(Point a, Point b) {
	float slope = (b.getY() - a.getY())/(b.getX()/a.getX());
	if(slope == 0) {
		return true;
	}
	return false;
}

bool Shapebuffer::isYMax(Point a, Point b, Point c) {
	if((b.getY() >= a.getY() && b.getY() >= c.getY()) ||
		(b.getY() <= a.getY() && b.getY() <= c.getY())){
			return true;
	}
	return false;
}

bool Shapebuffer::isRightTriangle(Point a, Point b, Point c) {
	cout << "[" << a.getX() << "][" << a.getY() << "] -> [" << b.getX() << "][" << b.getY() << "] -> ["  << c.getX() << "][" << c.getY() << "]";

	if((a.getY() == b.getY() && b.getX() == c.getX()) ||
		(a.getX() == b.getX() && b.getY() == c.getY())) {
			cout << "TRUUUU\n";
			return true;
	}
	cout << "nah, bruh\n";

	return false;
}


void Shapebuffer::setPixel(int x, int y, char pixel) {
	canvas[x][y] = pixel; 
}

void Shapebuffer::setPixel(float x, float y, char pixel){
	canvas[round(x)][round(y)] = pixel; 
}

char Shapebuffer::getPixel(int x, int y) {
	return canvas[x][y];
}

int Shapebuffer::round(float n) {
	float diff = n - int(n);
	if(diff < .5) {
		return int(n);
	} else {
		return int(n)+1;
	}
}
