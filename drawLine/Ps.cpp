#include "Ps.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <iterator>



Ps::Ps(void)
{
	fb = Framebuffer();
}


Ps::~Ps(void)
{
}

void Ps::input(string input) {
	if(!input.compare("stroke")) {
		//close current polygon
	}
	//split string
	istringstream iss(input);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));

	//get type
	string type = "";
	if(!tokens[0].compare("stroke")) {
		type = "stroke";
	} else if (!tokens[2].compare("lineto")) {
		type = "lineto";
	} else if (!tokens[2].compare("moveto")) {
		type = "moveto";
	} else if (!tokens[4].compare("Line")) {
		type = "Line";
	}

	//add line
	if(!type.compare("Line")) {
		Line* line = new Line(tokens[0], tokens[1], tokens[2], tokens[3]);
		addLine(line);
	} 
	//add polygon stuff
	else if(!type.compare("moveto")) {
		//start new polygon
		Polygon* polygon = new Polygon(tokens[0], tokens[1]);
		addPolygon(polygon);

	} else if(!type.compare("lineto")) {
		//append to new polygon
		Polygon &polygon = getPolygon();
		polygon.addPoint(tokens[0], tokens[1]);

	} else if(!type.compare("stroke")) {
		//finish current polygon
		Polygon &polygon = getPolygon();
		polygon.finishPolygon();
	}

}

void Ps::addLine(Line *l) {
	lines.push_back(*l);
}

void Ps::addPolygon(Polygon *p) {
	polygons.push_back(*p);
}

Polygon& Ps::getPolygon() {
	//find most recent polygon
	return polygons.at(polygons.size()-1);
}

void Ps::makeFramebuffer(bool dda) {
	//draw each line
	for(int i=0; i<lines.size(); i++){
		lines[i].draw(fb);
	}
	
	//draw each polygon
	for(int i=0; i<polygons.size(); i++){
		polygons[i].draw(fb);
		cout << endl;
	}
}

char Ps::getPixel(int x, int y) {
	return fb.getPixel(x, y);
}
