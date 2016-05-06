#include "light.hpp"
#include "window.hpp"
#include "initialiser.hpp"
#include "renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

int main(int argc, char ** argv) {
    marrow::Window window(500, 500, "Legolas");
    marrow::Camera camera(glm::vec3(0.0f, 0.0f, -10.0f), 0, 0);
    marrow::Geometry cabinet("obj/pino.obj");
    marrow::Texture plantex("tex/pino.png");
    marrow::Object cabob(&cabinet, &plantex, glm::mat4(1.0));
    marrow::Object cabob2(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 1.0)));
    marrow::Light light(glm::vec4(10.0f, 12.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(3.4f, 0.0f, 0.0f));
    marrow::Renderer renderer;
    renderer.addObject(&cabob);
    renderer.addObject(&cabob2);
    renderer.addLight(&light);
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
        camera.tick(span);
        renderer.render(camera);
        window.swap();
    }

    return 0;
}
