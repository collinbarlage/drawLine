#ifndef _FRAMEBUFFER_
#define _FRAMEBUFFER_
#include <string>
#include "Line.h"
using namespace std;
class Framebuffer
{
public:
	Framebuffer(void);

	~Framebuffer(void);

	//Methods
	char getPixel(int x, int y);
	void setPixel(int x, int y, char pixel);
	void setPixel(float x, float y, char pixel);
	int height;
	int width;
	int x;
	int y;
private:
	char canvas[500][500]; //default: 500px by 500px size
	int round(float n);
	
};

#endif