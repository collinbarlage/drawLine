#include "Framebuffer.h"
#include <iostream>
#include <fstream>

Framebuffer::Framebuffer(void)
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


Framebuffer::~Framebuffer(void)
{
}


void Framebuffer::setPixel(int x, int y, char pixel){
	canvas[x][y] = pixel; 
}

void Framebuffer::setPixel(float x, float y, char pixel){
	canvas[round(x)][round(y)] = pixel; 
}

char Framebuffer::getPixel(int x, int y) {
	return canvas[x][y];
}

int Framebuffer::round(float n) {
	float diff = n - int(n);
	if(diff < .5) {
		return int(n);
	} else {
		return int(n)+1;
	}
}
