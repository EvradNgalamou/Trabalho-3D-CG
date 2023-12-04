all:
	g++ -o trabalhocg main.cpp tinyxml2.cpp -lGL -lGLU -lglut

clean:
	rm -f *.o trabalhocg

