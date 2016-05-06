terrainShader.o: terrainShader.cpp terrainShader.hpp objectShader.o shader.o
	g++ -c -o terrainShader.o terrainShader.cpp -std=c++11
objectShader.o: objectShader.cpp objectShader.hpp shader.o
	g++ -c -o objectShader.o objectShader.cpp -std=c++11
shader.o: shader.cpp shader.hpp
	g++ -c -o shader.o shader.cpp -std=c++11
