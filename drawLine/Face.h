#ifndef _FACE_
#define _FACE_
#include <string>
#include <vector>
#include "Vertex.h"
#include "Shapebuffer.h"

using namespace std;

class Face
{
public:
	//constructors
	Face(void);
	Face(Vertex* a, Vertex* b, Vertex* c);
	 

	//destructor
	~Face(void);

	//methods
	void draw(Shapebuffer &sb);
	Vertex getVertex(int i);

private:
	vector<Vertex*> vertices;
};
#endif
