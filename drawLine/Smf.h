#include <vector>
#include <string>
#include "Framebuffer.h"
#include "Shapebuffer.h"
#include "Face.h"
#include "Vertex.h"
#include "Matrix.h"
#ifndef _SMF_
#define _SMF_
using namespace std;
class Framebuffer;

class Smf
{
public:
	//constructors
	Smf(void);

	//destructor
	~Smf(void);

	//Methods
	void input(string input);
	void makeFramebuffer();
	char getPixel(int x, int y);
	
	//public vars
	float scale;
	bool ortho;
	int angle;
	int xTrans;
	int yTrans;
	int xWorldMin;
	int yWorldMin;
	int xWorldMax;
	int yWorldMax;
	int xViewMin;
	int yViewMin;
	int xViewMax;
	int yViewMax;
	float xPrp;
	float yPrp;
	float zPrp;
	float xVrp;
	float yVrp;
	float zVrp;
	float xVpn;
	float yVpn;
	float zVpn;
	float xVup;
	float yVup;
	float zVup;
	float uMin;
	float uMax;
	float vMin;
	float vMax;
	float front;
	float back;



private:
	Framebuffer fb;
	vector<Vertex> vertices;
	vector<Face> faces;
	void setDefaultArgs();
};
#endif