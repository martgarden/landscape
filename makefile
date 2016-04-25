legolas: main.o window.o initialiser.o
	g++ -o legolas main.o window.o initialiser.o  -lGL -lGLU -lglut -lGLEW `pkg-config --libs IL` -std=c++11
main.o: main.cpp window.o
	g++ -c -o main.o main.cpp -std=c++11
window.o: window.hpp window.cpp initialiser.o
	g++ -c -o window.o window.cpp -std=c++11
initialiser.o: initialiser.hpp initialiser.cpp
	g++ -c -o initialiser.o initialiser.cpp -std=c++11
