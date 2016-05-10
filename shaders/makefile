waterShader.o: waterShader.cpp waterShader.hpp shader.o terrainShader.o objectShader.o skyboxShader.o
	g++ -c -o waterShader.o waterShader.cpp -std=c++11
skyboxShader.o: skyboxShader.cpp skyboxShader.hpp shader.o terrainShader.o objectShader.o
	g++ -c -o skyboxShader.o skyboxShader.cpp -std=c++11
terrainShader.o: terrainShader.cpp terrainShader.hpp objectShader.o shader.o
	g++ -c -o terrainShader.o terrainShader.cpp -std=c++11
objectShader.o: objectShader.cpp objectShader.hpp shader.o
	g++ -c -o objectShader.o objectShader.cpp -std=c++11
shader.o: shader.cpp shader.hpp
	g++ -c -o shader.o shader.cpp -std=c++11
