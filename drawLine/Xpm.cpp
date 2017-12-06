#include "Xpm.h"
#include <iostream>
#include <fstream>

Xpm::Xpm(void)
{
	ncolors = 2;
	charsperpixel = 1;
	xMax = 500;
	yMax = 500;
	xMin = 0;
	yMin = 0;
}


Xpm::~Xpm(void)
{
}

void Xpm::writePs(string filename, Ps &ps){
	filename = filename + ".xpm";
	//open file
	ofstream of;
	of.open (filename);
	//default xpm header
	of << "/*XPM*/\nstatic char *sco100[] = {\n";
	of << "\"" << xMax << " " << yMax << " " << ncolors << " " << charsperpixel << "\",\n";

	//TODO: loop through ps's colors
	of << "/*colors*/\n";
	of << "\"- c #ffffff\",\n";
	of << "\"# c #000000\",\n";

	//pixels
	of << "/*pixels*/\n";
	for(int j=yMax-1; j>=yMin; j--) {
		of << "\"";
		for(int i=xMin; i<xMax; i++) {
			of << ps.getPixel(i,j);
		}
		of << "\",\n";
	}

	//close file
	of << "};\n";
	of.close();

	//cout << "\nXPM file written to " << filename << endl << endl;
}

void Xpm::writeSmf(string filename, Smf &smf){
	filename = filename + ".xpm";
	//open file
	ofstream of;
	of.open (filename);
	//default xpm header
	of << "/*XPM*/\nstatic char *sco100[] = {\n";
	cout << "/*XPM*/\nstatic char *sco100[] = {\n";
	of << "\"" << xMax << " " << yMax << " " << ncolors << " " << charsperpixel << "\",\n";
	cout << "\"" << xMax << " " << yMax << " " << ncolors << " " << charsperpixel << "\",\n";

	//TODO: loop through ps's colors
	of << "/*colors*/\n";
	cout << "/*colors*/\n";
	of << "\"- c #000000\",\n";
	cout << "\"- c #000000\",\n";
	of << "\"# c #ff0000\",\n";
	cout << "\"# c #ff0000\",\n";

	//pixels
	of << "/*pixels*/\n";
	cout << "/*pixels*/\n";
	for(int j=yMax-1; j>=yMin; j--) {
		of << "\"";
		cout << "\"";
		for(int i=xMin; i<xMax; i++) {
			of << smf.getPixel(i,j);
			cout << smf.getPixel(i,j);
		}
		of << "\",\n";
		cout << "\",\n";
	}


	//close file
	of << "};\n";
	cout << "};\n";
	of.close();

	//cout << "\nXPM file written to " << filename << endl << endl;
}
