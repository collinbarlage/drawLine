#include "Smf.h"
#include <iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <iterator>



Smf::Smf(void)
{
	fb = Framebuffer();
	front = .6;
	back = -.6;
}


Smf::~Smf(void)
{
}

void Smf::input(string input) {
	if(!input.compare("stroke")) {
		//close current polygon
	}
	//split string
	istringstream iss(input);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));

	if(!tokens[0].compare("v")) {
		//add vertex
		Vertex* v = new Vertex(stof(tokens[1]), stof(tokens[2]), stof(tokens[3]));
		vertices.push_back(*v);
	} else if (!tokens[0].compare("f")) {
		//create face
		Face* f = new Face(&vertices[stoi(tokens[1])-1], &vertices[stoi(tokens[2])-1], &vertices[stoi(tokens[3])-1]);
		faces.push_back(*f);
	} 


}


void Smf::makeFramebuffer() {
	//cout << "ortho: " << ortho << endl;

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

	//orient camera
	Matrix VPN = Matrix(xVpn, yVpn, zVpn, 1);
	Matrix VUP = Matrix(xVup, yVup, zVup, 1);
	Matrix u = VUP.cross(VPN);
	//cout << "u:\n";
	u.print();
	Matrix v = VPN.cross(u);
	//cout << "v:\n";
	v.print();

	//rotation matrix
	Matrix rotation = Matrix(u.get(0,3), v.get(0,3), VPN.get(0,3), 0);
	rotation.addColumn(u.get(0,2), v.get(0,2), VPN.get(0,2), 0);
	rotation.addColumn(u.get(0,1), v.get(0,1), VPN.get(0,1), 0);
	rotation.addColumn(0, 0, 0, 1);
	//cout << "Roataion:\n";
	rotation.print();

	//translation matrix
	Matrix translation = Matrix(1, 0, 0, 0);
	translation.addColumn(0, 1, 0, 0);
	translation.addColumn(0, 0, 1, 0);
	translation.addColumn(-1*xVrp, -1*yVrp, -1*zVrp, 1);
	//cout << "Translation:\n";
	translation.print();

	//calculate view matrix
	Matrix mView = rotation.multiply(translation);
	//cout << "mView:\n";
	mView.print();

	//set up projection matrix
	Matrix mProj = Matrix();
	if(ortho) {
		//orthographic AKA paralell proj
		//cout << "ORTHO\n";
		mProj.addColumn(2/(uMax - uMin), 0, 0, 0);
		mProj.addColumn(0, 2/(vMax-vMin), 0, 0);
		mProj.addColumn(((uMax+uMin)-(2*xPrp))/((uMax-uMin)*zPrp), 
			((vMax+vMin)-(2*yPrp))/((vMax-vMin)*zPrp), 
			1/(front-back), 0);
		mProj.addColumn((-1*(uMax+uMin)/(uMax-uMin)), 
			(-1*(vMax+vMin)/(vMax-vMin)), 
			(-1*(front/(front-back))), 1); 

	} else {
		//perspective proj
		//cout << "PERSPECTIVE\n";
		mProj.addColumn((2*zPrp)/((uMax-uMin)*(zPrp-back)), 0, 0, 0);
		mProj.addColumn(0, (2*zPrp)/((vMax-vMin)*(zPrp-back)), 0, 0);
		mProj.addColumn(((uMax+uMin-2)*xPrp)/((uMax-uMin)*(zPrp-back)), 
			((vMax+vMin-2)*yPrp)/((vMax-vMin)*(zPrp-back)), 
			1/(zPrp-back), 0);
		mProj.addColumn(-1*((uMax+uMin)*zPrp)/((uMax-uMin)*(zPrp-back)), 
			-1*((vMax+vMin)*zPrp)/((vMax-vMin)*(zPrp-back)), 
			-1*zPrp/(zPrp-back), 1);
	}


	//cout << "mProj:\n";
	mProj.print();

	Matrix mProjView = mProj.multiply(mView);

	//apply projected view matrix to all points
	for(int i=0; i<vertices.size(); i++) {
		vertices.at(i).multiply(mProjView);
	}
	//clip 3d

	//project 3d to 2d
	//create lines
	Point points[3];
	Line A, B, C;
	float zDiv;
	for(int i=0; i<faces.size(); i++) {
		if(ortho) {
			//create points 
			for(int p=0; p<3; p++) {
				points[p] = Point(faces.at(i).getVertex(p).getFrameX(), 
					faces.at(i).getVertex(p).getFrameY());
			}
		} else {
			//create perspective points
			for(int p=0; p<3; p++) {
				////cout << "<" << faces.at(i).getVertex(0).getX() << ", " << faces.at(i).getVertex(0).getY() << ">  -->  ";
				zDiv = faces.at(i).getVertex(p).getZ();
				////cout << "  zDiv: " << zDiv << "  "; 
				points[p] = Point(-1*faces.at(i).getVertex(p).getX()/zDiv*250 + 250, 
					-1*faces.at(i).getVertex(p).getY()/zDiv*250 +250);
				////cout << "<" << points[p].getX() << ", " << points[p].getY() << "> \n";
			}
		}

		//2d transformation
		for(int p=0; p<3; p++) {
			//scale
			points[p].scale(scale, scale);
			//rotate
			points[p].rotate(angle);
			//translate
			points[p].trans(xTrans, yTrans);

			//transform to viewport
			points[p].trans(-1 * xWorldMin, -1 * yWorldMin); 
			points[p].scale(xViewScale, yViewScale);
			points[p].trans(xViewMin, yViewMin); 
		}

		//create lines
		A = Line(points[0], points[1], fb);
		B = Line(points[1], points[2], fb);
		C = Line(points[2], points[0], fb);
		//draw lines
		A.drawToFrame(fb);
		B.drawToFrame(fb);
		C.drawToFrame(fb);
	}
}

char Smf::getPixel(int x, int y) {
	return fb.getPixel(x, y);
}

void Smf::setDefaultArgs() {
	//cout << xPrp << endl << yPrp << endl;
}
