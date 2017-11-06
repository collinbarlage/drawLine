#ifndef _XPM_
#define _XPM_
#include <string>
#include "Ps.h"
using namespace std;
class Xpm
{
public:
	Xpm(void);

	~Xpm(void);

	void write(string filename, Ps &ps);


private:
	int width;
	int height;
	int ncolors;
	int charsperpixel;
};

#endif