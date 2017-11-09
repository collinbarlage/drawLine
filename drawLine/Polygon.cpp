
#include "Polygon.h"
#include <iostream>

Polygon::Polygon(void)
{
}


Polygon::Polygon(string x, string y) {
	valid = false;
	addPoint(x, y);
	//setup corners
	corners[0] = 0;
	corners[1] = 0;
	corners[2] = 0;
	corners[3] = 0;
}

Polygon::~Polygon(void)
{
}

void Polygon::draw(Shapebuffer &sb) {
	cout << "drawing polygon... \n";
	Polygon temp = Polygon();
	Line L;


	//clip
	int i = 0;
	L = Line(points.at(0), points.at(1), sb);
	int isNotInBounds = L.isNotInBounds(sb.width, sb.height);

	while(isNotInBounds == 2 || isNotInBounds == 3) { //while starting point is out of bounds
			cout << "WAT" << i << endl;

		L = Line(points.at(i), points.at(i+1), sb);

		//get valid starting point
		if(isNotInBounds == 3 && !L.isValid()) { //out -> out
			i++; //skip this sillyness 
		} else if(isNotInBounds == 3) { // out -> out 
			replacePoint(i, L.getClipPoint1(sb));
		} else { // out -> in
			L.clip(sb.x, sb.y);
			replacePoint(i, L.getPoint(1));
		}

		int isNotInBounds = L.isNotInBounds(sb.x, sb.y);

		//ignore silly polygons
		if (i >= points.size()-1) {
			return; 
		}
	}
	//add first point
	temp.addPoint(&points.at(0));
	//go through remaining points
	for(i; i<points.size()-1; i++) {
		//cout << i <<" ~ (" << points.at(i).getX() << ", " << points.at(i).getY() << ") -> (" << points.at(i+1).getX() << ", " << points.at(i+1).getY() << ")  ~~~>\n";

		//set line
		L = Line(points.at(i), points.at(i+1), sb);
		isNotInBounds = L.isNotInBounds(sb.x, sb.y);

		if(isNotInBounds == 0) { //in bounds
			temp.addPoint(&points.at(i+1));
		} else if(isNotInBounds == 1) { //in -> out
			//get clipped point 
			const Point point = L.getClipPoint2(sb);
			//cout << "in -> out ... adding point (" << point.getX() << ", " << point.getY() << ")\n";
			temp.addPoint(&point);

		} else if(isNotInBounds == 2) { //out -> in
			//get clipped point 
			const Point point = L.getClipPoint1(sb);
			//cout << "out -> in ... adding points (" << point.getX() << ", " << point.getY() << ") and ("<< points.at(i+1).getX() << ", " << points.at(i+1).getY() << ")\n";
			temp.addPoint(&point);
			temp.addPoint(&points.at(i+1));
		} else { //out -> out
			//get clipped points?
			if(L.isValid()) {
				const Point point1 =  L.getClipPoint1(sb);
				const Point point2 =  L.getClipPoint2(sb);
				//cout << "out -> out ... adding points (" << point1.getX() << ", " << point1.getY() << ") and ("<< point2.getX() << ", " << point2.getY() << ")\n";

				temp.addPoint(&point1);
				temp.addPoint(&point2);
			}
		}
	}
	//don't forget to add the last point!
	const Point point = points.at(0);
	temp.addPoint(&point);




	//loop through all points and draw
	for(int i=0; i < temp.size()-1; i++) {
		cout << "    ";
		//draw line
		L = Line(temp.getPoint(i), temp.getPoint(i+1), sb);
		cout << "L = (" << L.getPoint(1).getX() << ", " << L.getPoint(1).getY() << "), (" << L.getPoint(2).getX() << ", " << L.getPoint(2).getY() << ")\n";
		L.draw(sb);
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

void Polygon::checkCorners(int side, int inOut) {

}
