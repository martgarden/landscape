#include "light.hpp"
#include "window.hpp"
#include "initialiser.hpp"
#include "renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

std::string toStr(int no) {
    std::string es;
    if(no < 0) {
        es += '-';
        no = -no;
    }
    es += char(no + 48);
    return es;
}

int main(int argc, char ** argv) {
    marrow::Window window(1000, 800, "Legolas");
    marrow::Camera camera(glm::vec3(0.0f, 30.0f, 0.0f), 0, 0);
    marrow::Renderer renderer;
    marrow::Geometry treeg("obj/npino.obj");
    marrow::Texture treet("tex/pino.png");
    marrow::Geometry houseg("obj/house.obj");
    marrow::Texture houset("tex/house.png");
    marrow::Geometry lampg("obj/nlamp.obj");
    marrow::Texture lampt("tex/lamp.png");
    std::ifstream ofile("obj/objects.txt");
    std::string line, word;
    while(std::getline(ofile, line)) {
        std::istringstream is(line);
        is>>word;
        if(word == "house") {
            float x, y, z, rot;
            is>>x>>y>>z>>rot;
            renderer.addObject(new marrow::Object(&houseg, &houset, glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f))));
        }
        if(word == "tree") {
            float x, y, z, rot;
            is>>x>>y>>z>>rot;
            renderer.addObject(new marrow::Object(&treeg, &treet, glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.0f, 1.0f, 0.0f))));
        }
        else if(word == "lamp") {
            float x, y, z, r, g, b;
            is>>x>>y>>z>>r>>g>>b;
            renderer.addObject(new marrow::Object(&lampg, &lampt, glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z))));
            glm::vec3 color(r, g, b);
            renderer.addLight(new marrow::Light(glm::vec4(x, y + 3.2f, z, 1.0f), 0.1f*color, 0.6f*color, color, glm::vec3(1.0, 0.01, 0.001)));
        }
    }

    marrow::Light sun(glm::vec4(10.0f, 10.0f, 10.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(3.4f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    marrow::Light moon(glm::vec4(10.0f, 10.0f, 10.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(3.4f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    marrow::Texture day = marrow::Texture::loadCubeFromFiles("tex/Day", ".png");
    marrow::Texture night = marrow::Texture::loadCubeFromFiles("tex/Night", ".png");
    marrow::Skybox skybox(&day, &night, &sun, &moon, 50.0f);
    renderer.addLight(&sun);
    renderer.addLight(&moon);
    renderer.setSkybox(&skybox);
    std::string hs("tex/height_map");
    std::string bs("tex/brgb_map");
    marrow::Texture background("tex/dirt.png");
    marrow::Texture red("tex/sand.png");
    marrow::Texture green("tex/grass.png");
    marrow::Texture blue("tex/Cobblestone.png");
    for(int i = -2; i < 2; i++) {
        for(int j = -2; j < 2; j++) {
            renderer.addTerrain(std::make_pair(i, j), new marrow::Terrain(new marrow::Texture((hs+toStr(i)+toStr(j)+".png").c_str()), new marrow::Texture((bs+toStr(i)+toStr(j)+".png").c_str()), &background, &red, &green, &blue));
        }
    }
    marrow::Water water(30.0f, 50.0f, 210.0f, 210.0f);
    renderer.setWaterLevel(22.0f);
    renderer.addWater(&water);
    bool done = false;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now(), t2;
    double span;
    while(!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_l:
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            break;
                    }
                    break;
            }
        }
        t2 = std::chrono::high_resolution_clock::now();
        span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t).count();
        t = t2;
        std::cout << 1/span << std::endl;
        camera.tick(span);
        skybox.tick(span);
        renderer.render(camera);
        window.swap();
    }

    return 0;
}
