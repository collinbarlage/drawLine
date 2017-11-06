#include "Xpm.h"
#include <iostream>
#include <fstream>

Xpm::Xpm(void)
{
	width = 500;
	height = 500;
	ncolors = 2;
	charsperpixel = 1;
}


Xpm::~Xpm(void)
{
}

void Xpm::write(string filename, Ps &ps){
	filename = filename + ".xpm";
	//open file
	ofstream of;
	of.open (filename);
	//default xpm header
	of << "/*XPM*/\nstatic char *sco100[] = {\n";
	of << "\"" << width << " " << height << " " << ncolors << " " << charsperpixel << "\",\n";

	//TODO: loop through ps's colors
	of << "/*colors*/\n";
	of << "\"- c #ffffff\",\n";
	of << "\"# c #000000\",\n";

	//pixels
	of << "/*pixels*/\n";
	for(int j=height-1; j>=0; j--) {
		of << "\"";
		for(int i=0; i<width; i++) {
			of << ps.getPixel(i,j);
		}
		of << "\",\n";
	}

	//close file
	of << "};\n";
	of.close();

	cout << "\nXPM file written to " << filename << endl << endl;
}
