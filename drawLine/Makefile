default: A6

A6.o: drawLine.cpp Point.cpp Point.h Line.cpp Line.h Ps.cpp Ps.h Xpm.cpp Xpm.h Framebuffer.cpp Framebuffer.h Polygon.cpp Polygon.h Shapebuffer.cpp Shapebuffer.h Matrix.cpp Matrix.h Smf.cpp Smf.h Vertex.cpp Vertex.h
	g++ -std=c++11 -c drawLine.cpp -o A6.o
	g++ -std=c++11 -c Point.cpp -o Point.o
	g++ -std=c++11 -c Line.cpp -o Line.o
	g++ -std=c++11 -c Ps.cpp -o Ps.o
	g++ -std=c++11 -c Xpm.cpp -o Xpm.o
	g++ -std=c++11 -c Framebuffer.cpp -o Framebuffer.o
	g++ -std=c++11 -c Polygon.cpp -o Polygon.o
	g++ -std=c++11 -c Shapebuffer.cpp -o Shapebuffer.o
	g++ -std=c++11 -c Matrix.cpp -o Matrix.o
	g++ -std=c++11 -c Matrix.cpp -o Matrix.o
	g++ -std=c++11 -c Smf.cpp -o Smf.o
	g++ -std=c++11 -c Vertex.cpp -o Vertex.o


A6: A6.o Point.o Line.o Ps.o Xpm.o Framebuffer.o Polygon.o Shapebuffer.o Matrix.o Smf.o Vertex.o
	g++ A6.o Point.o Line.o Ps.o Xpm.o Framebuffer.o Polygon.o Shapebuffer.o Matrix.o Smf.o Vertex.o -o A6
	rm -f *.o

clean:
	-rm -f A6
