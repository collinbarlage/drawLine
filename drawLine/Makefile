default: A5

A5.o: drawLine.cpp Point.cpp Point.h Line.cpp Line.h Ps.cpp Ps.h Xpm.cpp Xpm.h Framebuffer.cpp Framebuffer.h Polygon.cpp Polygon.h Shapebuffer.cpp Shapebuffer.h 
	g++ -std=c++11 -c drawLine.cpp -o A5.o
	g++ -std=c++11 -c Point.cpp -o Point.o
	g++ -std=c++11 -c Line.cpp -o Line.o
	g++ -std=c++11 -c Ps.cpp -o Ps.o
	g++ -std=c++11 -c Xpm.cpp -o Xpm.o
	g++ -std=c++11 -c Framebuffer.cpp -o Framebuffer.o
	g++ -std=c++11 -c Polygon.cpp -o Polygon.o
	g++ -std=c++11 -c Shapebuffer.cpp -o Shapebuffer.o

A5: A5.o Point.o Line.o Ps.o Xpm.o Framebuffer.o Polygon.o Shapebuffer.o
	g++ A5.o Point.o Line.o Ps.o Xpm.o Framebuffer.o Polygon.o Shapebuffer.o -o A5
	rm -f *.o

clean:
	-rm -f A5
