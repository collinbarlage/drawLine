
#include "Polygon.h"
#include <iostream>

Polygon::Polygon(void)
{
}


Polygon::Polygon(string x, string y) {
	valid = false;
	addPoint(x, y);
}

Polygon::~Polygon(void)
{
}

void Polygon::draw(Framebuffer &fb) {
	cout << "drawing polygon... \n";
	Polygon temp = Polygon();
	Line L;

	//check for clipping
	int i = 0;

	//clip
	L = Line(points.at(0), points.at(1), fb);
	int isNotInBounds = L.isNotInBounds(fb.width, fb.height);

	while(isNotInBounds == 2 || isNotInBounds == 3) { //while starting point is out of bounds
		//cout << i <<" ~ ";

		//get valid starting point
		if(isNotInBounds == 3) { //out -> out
			i++; //skip this sillyness
		} else { // out -> in
			L.clip(fb.x, fb.y);
			replacePoint(i, L.getPoint(1));
		}

		int isNotInBounds = L.isNotInBounds(fb.x, fb.y);

		//ignore silly polygons
		if (i > points.size()) {
			return; 
		}

	}
	//add first point
	temp.addPoint(&points.at(0));
	//go through remaining points
	for(i; i<points.size()-1; i++) {
		cout << i <<" ~ (" << points.at(i).getX() << ", " << points.at(i).getY() << ") -> (" << points.at(i+1).getX() << ", " << points.at(i+1).getY() << ")  ~~~>\n";

		//set line
		L = Line(points.at(i), points.at(i+1), fb);
		isNotInBounds = L.isNotInBounds(fb.x, fb.y);

		if(isNotInBounds == 0) { //in bounds
			temp.addPoint(&points.at(i+1));
		} else if(isNotInBounds == 1) { //in -> out
			//get clipped point 
			L.clip(fb.x, fb.y);
			cout << "in -> out ... adding point (" << L.getPoint(2).getX() << ", " << L.getPoint(2).getY() << ")\n";
			const Point point = L.getClipPoint(fb);
			temp.addPoint(&point);

		} else if(isNotInBounds == 2) { //out -> in
			//get clipped point 
			//cout << "clipping line point (" << L.getPoint(1).getX() << ", " << L.getPoint(1).getY() << ") -> ("<<L.getPoint(2).getX() << ", " << L.getPoint(2).getY()<<")\n";
			//cout << "clipping on (" << fb.x <<")\n";
			L.clip(fb.x, fb.y);
			cout << "out -> in ... adding point (" << L.getPoint(1).getX() << ", " << L.getPoint(1).getY() << ")\n";
			
			const Point point = L.getClipPoint(fb); 
			temp.addPoint(&point);
			temp.addPoint(&points.at(i+1));

		}
	}
	//don't forget to add the last point!
	const Point point = L.getPoint(2);
	temp.addPoint(&point);




	//loop through all points and draw
	for(int i=0; i < temp.size()-1; i++) {
		cout << "    ";
		//draw line
		L = Line(temp.getPoint(i), temp.getPoint(i+1), fb);
		cout << "L = (" << L.getPoint(1).getX() << ", " << L.getPoint(1).getY() << "), (" << L.getPoint(2).getX() << ", " << L.getPoint(2).getY() << ")\n";
		L.draw(fb);
	}
}

void Polygon::finishPolygon() {
	valid = true;
}

void Polygon::addPoint(string x, string y) {
	Point *p = new Point(stoi(x), stoi(y));
	points.push_back(*p);
}

void Polygon::replacePoint(int i, Point p) {
	points[i] = p;
}

void Polygon::addPoint(const Point *p) {
	points.push_back(*p);
}

Point Polygon::getPoint(int i) {
	return points.at(i);
}

int Polygon::size() {
	return points.size();
}
