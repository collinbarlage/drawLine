#ifndef _XPM_
#define _XPM_
#include <string>
#include "Ps.h"
using namespace std;
class Xpm
{
public:
	Xpm(void);
	Xpm(int xViewMin, int yViewMin, int xViewMax, int yViewMax);

	~Xpm(void);

	void write(string filename, Ps &ps);


private:
	int ncolors;
	int charsperpixel;
	int xMin;
	int yMin;
	int xMax;
	int yMax;
};

#endif