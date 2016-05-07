#include "light.hpp"
#include "window.hpp"
#include "initialiser.hpp"
#include "renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

int main(int argc, char ** argv) {
    marrow::Window window(1000, 800, "Legolas");
    marrow::Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 0, 0);
    marrow::Geometry cabinet("obj/pino.obj");
    marrow::Texture plantex("tex/pino.png");
    marrow::Object cabob(&cabinet, &plantex, glm::mat4(1.0));
    marrow::Object cabob2(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 1.0)));
    marrow::Object cabob3(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 10.0)));
    marrow::Geometry houseg("obj/house.obj");
    marrow::Texture houset("tex/house.png");
    marrow::Object house(&houseg, &houset, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 25.0)));;
    marrow::Light light(glm::vec4(10.0f, 5.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(3.4f, 0.0f, 0.0f));
    marrow::Renderer renderer;
    renderer.addObject(&cabob);
    renderer.addObject(&cabob2);
    renderer.addObject(&cabob3);
    renderer.addObject(&house);
    renderer.addLight(&light);
    marrow::Texture heights("tex/height_map.png");
    marrow::Texture cobble("tex/Cobblestone.png");
    marrow::Terrain terrain(&heights, &cobble);
    renderer.addTerrain(&terrain);
    bool done = false;
    std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now(), t2;
    double span;
    while(!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    done = true;
            }
        }
        t2 = std::chrono::high_resolution_clock::now();
        span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t).count();
        t = t2;
        std::cout << 1/span << std::endl;
        camera.tick(span);
        renderer.render(camera);
        window.swap();
    }

    return 0;
}
