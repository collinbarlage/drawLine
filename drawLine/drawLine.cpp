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
#include "Smf.h"
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

bool getProjection(vector<string> args){
	args.push_back("");
	for (int i=0; i < args.size(); i++) {
		if (!args[i].compare("-P")) {
			return true;
		}
	}
	return false;
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

float getFloatArg(vector<string> args, string arg) {
	args.push_back("");
	for(int i=0; i < args.size(); i++) {
		if(!args[i].compare(arg)) {
			if ((!args[i+1].compare("")) || (!args[i+1].substr(0,1).compare("-"))) {
				return NULL;
			} else {
				return stof(args[i+1]);
			}
		}
	}
	//default values
	if(!arg.compare("-z") || !arg.compare("-R")) {
		return 1;
	} else if(!arg.compare("-w")) {
		return -1; //1?
	} else if((!arg.compare("-u")) || (!arg.compare("-v"))) {
		return -0.7;
	} else if((!arg.compare("-U")) || (!arg.compare("-V"))) {
		return 0.7;
	} else {
		return 0;
	}
	return NULL;
}





int main(int argc, const char * argv[])
{
	cout << "\n-------------COOL ~~ DRAWER-------------\n";
	cout <<   "             Made by Collin\n\n";

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
	cout << "Loading file from " << fileName << " ...\n";
	Ps ps = Ps(); //construct ps object
	Ps *psPointer = &ps; //construct ps object
	Smf smf = Smf(); //construct smf object
	Smf *smfPointer = &smf; //make pointer
	ifstream infile(fileName.c_str());
	string fin;
	bool begin = false;




	if(fileName.find(".ps") != string::npos) {
		//read in ps file

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
		xpm.writePs(fileName.substr(0, fileName.find(".ps")), ps);

	} else {
		//read in smf file

		//set args
		smf.scale      = getScale(args);
		smf.ortho      = getProjection(args);
		smf.angle      = getArg(args, "-r");
		smf.xTrans     = getArg(args, "-m");
		smf.yTrans     = getArg(args, "-n");
		smf.xWorldMin  = getArg(args, "-a");		
		smf.yWorldMin  = getArg(args, "-b");
		smf.xWorldMax  = getArg(args, "-c");
		smf.yWorldMax  = getArg(args, "-d");
		smf.xViewMin   = getArg(args, "-j");
		smf.yViewMin   = getArg(args, "-k");
		smf.xViewMax   = getArg(args, "-o");
		smf.yViewMax   = getArg(args, "-p");
		smf.xPrp       = getFloatArg(args, "-x");
		smf.yPrp       = getFloatArg(args, "-y");
		smf.zPrp       = getFloatArg(args, "-z");
		smf.xVrp       = getFloatArg(args, "-X");
		smf.yVrp       = getFloatArg(args, "-Y");
		smf.zVrp       = getFloatArg(args, "-Z");
		smf.xVpn       = getFloatArg(args, "-q");
		smf.yVpn       = getFloatArg(args, "-r");
		smf.zVpn       = getFloatArg(args, "-w");
		smf.xVup       = getFloatArg(args, "-Q");
		smf.yVup       = getFloatArg(args, "-R");
		smf.zVup       = getFloatArg(args, "-W");
		smf.uMin       = getFloatArg(args, "-u");
		smf.uMax       = getFloatArg(args, "-U");
		smf.vMin       = getFloatArg(args, "-v");
		smf.vMax       = getFloatArg(args, "-V");

		while (getline(infile, fin)) {
			istringstream iss(fin);
			smf.input(fin);
		}

		smf.makeFramebuffer();

		//write image
		Xpm xpm = Xpm();
		xpm.writeSmf(fileName.substr(0, fileName.find(".smf")), smf);

	}




	return 0;
}
