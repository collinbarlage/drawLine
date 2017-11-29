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
	//for(int i=0; i<lines.size(); i++){
	//lines[i].draw(fb);
	//}


	//set up world view and viewport
	float xWorldScale = 1; 
	float yWorldScale = 1;
	float xViewScale = 1;
	float yViewScale = 1;
	if(!(xWorldMax == 0 && xWorldMin == 0)) {
		xWorldScale = float(fb.width)/(float(xWorldMax - xWorldMin));
		xViewScale = (float(xViewMax - xViewMin))/(float(xWorldMax - xWorldMin));
	}
	if(!(yWorldMax == 0 && yWorldMin == 0)) {
		yWorldScale = float(fb.height)/(float(yWorldMax - yWorldMin));
		yViewScale = (float(yViewMax - yViewMin))/(float(yWorldMax - yWorldMin));
	} 

	//transform each polygon
	for(int i=0; i<polygons.size(); i++) {
		
		//transform to world
		//polygons.at(i).trans(-1 * xWorldMin, -1 * yWorldMin); 
		//polygons.at(i).scale(xWorldScale, yWorldScale);
		//cout << "scale: " << xWorldScale << ", " << yWorldScale << endl;
		

		//scale
		polygons.at(i).scale(scale, scale);
		//rotate
		polygons.at(i).rotate(rotation);
		//translate
		polygons.at(i).trans(xTrans, yTrans);

		//transform to viewport
		polygons.at(i).trans(-1 * xWorldMin, -1 * yWorldMin); 
		polygons.at(i).scale(xViewScale, yViewScale);
		polygons.at(i).trans(xViewMin, yViewMin); 
	}

	//add each polygon to shape buffer
	vector<Shapebuffer> shapes;
	for(int i=0; i<polygons.size(); i++){
		Shapebuffer shape = Shapebuffer();
		polygons[i].draw(shape);
		shapes.push_back(shape);
		cout << endl;
	}

	//fill, then draw each shape
	for(int i=0; i<shapes.size(); i++){
		//shapes[i].fill(polygons[i], '#');
		shapes[i].draw(fb);
	}
}

char Ps::getPixel(int x, int y) {
	return fb.getPixel(x, y);
}
