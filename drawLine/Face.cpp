#include "Face.h"
#include <iostream>

Face::Face(void)
{
}


Face::Face(Vertex* a, Vertex* b, Vertex* c) {
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
}

Face::~Face(void)
{
}

void Face::draw(Shapebuffer &sb) {
	cout << "drawing Face... \n";
	
}

