legolas: main.o window.o initialiser.o light.o geometry.o object.o camera.o renderer.o texture.o terrain.o skybox.o
	g++ -o legolas main.o window.o initialiser.o  light.o geometry.o object.o camera.o renderer.o texture.o terrain.o skybox.o shaders/shader.o shaders/objectShader.o shaders/terrainShader.o shaders/skyboxShader.o -lGL -lGLU -lGLEW `pkg-config --libs IL sdl2` -std=c++11
main.o: main.cpp window.o
	g++ -c -o main.o main.cpp -std=c++11
window.o: window.hpp window.cpp initialiser.o
	g++ -c -o window.o window.cpp -std=c++11
initialiser.o: initialiser.hpp initialiser.cpp
	g++ -c -o initialiser.o initialiser.cpp -std=c++11
light.o: light.hpp light.cpp
	g++ -c -o light.o light.cpp -std=c++11
geometry.o: geometry.hpp geometry.cpp
	g++ -c -o geometry.o geometry.cpp -std=c++11
object.o: object.hpp object.cpp geometry.o
	g++ -c -o object.o object.cpp -std=c++11
camera.o: camera.hpp camera.cpp
	g++ -c -o camera.o camera.cpp -std=c++11
renderer.o: renderer.hpp renderer.cpp
	g++ -c -o renderer.o renderer.cpp -std=c++11
texture.o: texture.hpp texture.cpp
	g++ -c -o texture.o texture.cpp -std=c++11
terrain.o: terrain.hpp terrain.cpp
	g++ -c -o terrain.o terrain.cpp -std=c++11
skybox.o: skybox.hpp skybox.cpp
	g++ -c -o skybox.o skybox.cpp -std=c++11
