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

float getScale(vector<string> args) {
	args.push_back("");
	for (int i=0; i < args.size(); i++) {
		if (!args[i].compare("-s")) {
			if ((!args[i+1].compare("")) || (!args[i+1].substr(0,1).compare("-"))) {
				return 1.0;
			} else {
				return stof(args[i+1]);
			}
		}
	}
	return 1.0;
}

int getArg(vector<string> args, string arg) {
	args.push_back("");
	for(int i=0; i < args.size(); i++) {
		if(!args[i].compare(arg)) {
			if ((!args[i+1].compare("")) || (!args[i+1].substr(0,1).compare("-"))) {
				return NULL;
			} else {
				return stoi(args[i+1]);
			}
		}
	}
	return NULL;
}


int main(int argc, const char * argv[])
{
	//cout << "\n-------------COOL ~~ DRAWER-------------\n";
	//cout <<   "             Made by Collin\n\n";

	//get args
	vector<string> args(argv, argv + argc);
	string fileName;
	bool dda = true;

	//set filename
	if (argc == 1) {
		fileName = "hw1.ps";
	} else {
		fileName = getFilename(args);
		dda = getDDA(args);
	}


	//load file 
	//cout << "Loading file from " << fileName << " ...\n";
	Ps ps = Ps(); //construct ps object
	Ps *psPointer = &ps; //construct ps object
	ifstream infile(fileName.c_str());
	string fin;
	bool begin = false;


	//set args
	ps.scale     = getScale(args);
	ps.rotation  = getArg(args, "-r");
	ps.xTrans    = getArg(args, "-m");
	ps.yTrans    = getArg(args, "-n");
	ps.xWorldMin = getArg(args, "-a");		
	ps.yWorldMin = getArg(args, "-b");
	ps.xWorldMax = getArg(args, "-c");
	ps.yWorldMax = getArg(args, "-d");
	ps.xViewMin  = getArg(args, "-j");
	ps.yViewMin  = getArg(args, "-k");
	ps.xViewMax  = getArg(args, "-o");
	ps.yViewMax  = getArg(args, "-p");

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
