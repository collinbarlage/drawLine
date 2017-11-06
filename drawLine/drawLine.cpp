#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>  
#include <stdarg.h>  
#include <fstream>
#include <sstream>
#include "Framebuffer.h"
#include "Polygon.h"
#include "Line.h"
#include "Ps.h"
#include "Xpm.h"
using namespace std;

bool getDDA(vector<string> args) { 
	for (int i=0; i< args.size(); i++) {
		if (!args[i].compare("-x")) { 
			return false;
		}
	}
	return true;
}

string getFilename(vector<string> args){
	args.push_back("");
	for (int i=0; i < args.size(); i++) {
		if (!args[i].compare("-f")) {
			if ((!args[i+1].compare("")) || (!args[i+1].substr(0,1).compare("-"))) {
				return "hw1.ps";
			} else {
				return args[i+1];
			}
		}
	}
	return "hw1.ps";
}


int main(int argc, const char * argv[])
{
	cout << "\n-------------COOL ~~ DRAWER-------------\n";
	cout <<   "             Made by Collin\n\n";

	//get args
	vector<string> args(argv, argv + argc);
	string fileName;
	bool dda = true;

	//get filename
	if (argc == 1) {
		fileName = "hw1.ps";
	} else {
		fileName = getFilename(args);
		dda = getDDA(args);
	}
	//load file 
	cout << "Loading file from " << fileName << " ...\n";
	Ps ps = Ps(); //construct ps object
	Ps *psPointer = &ps; //construct ps object
	ifstream infile(fileName.c_str());
	string fin;
	bool begin = false;

	//read in ps file
	while (getline(infile, fin)) {
		istringstream iss(fin);
		if(!fin.compare("%%%BEGIN")) {
			begin = true;
		}
		else if(!fin.compare("%%%END")) {
			break;
		}
		else if(begin && fin.length() > 1){
			ps.input(fin);
		}
	}

	//draw with choosen algorithm
	ps.makeFramebuffer(true);
	//cout << "Using clipping algorithm: ";
	//dda? cout << "Cohen-Sutherland\n\n": cout << "Cyrus-Beck\n\n";

	//write image
	Xpm xpm = Xpm();
	xpm.write(fileName.substr(0, fileName.find(".ps")), ps);

	return 0;
}
