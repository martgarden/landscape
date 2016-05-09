#include "light.hpp"
#include "window.hpp"
#include "initialiser.hpp"
#include "renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    marrow::Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), 0, 0);
    marrow::Geometry cabinet("obj/pino.obj");
    marrow::Texture plantex("tex/pino.png");
    marrow::Object cabob(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 20.0, 1.0)));
    marrow::Object cabob2(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 1.0)));
    marrow::Object cabob3(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 10.0)));
    marrow::Geometry houseg("obj/house.obj");
    marrow::Texture houset("tex/house.png");
    marrow::Object house(&houseg, &houset, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 25.0)));;
    marrow::Light light(glm::vec4(10.0f, 10.0f, 10.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(3.4f, 0.0f, 0.0f));
    marrow::Light light2(glm::vec4(10.0f, 10.0f, 10.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(3.4f, 0.0f, 0.0f));
    marrow::Texture day = marrow::Texture::loadCubeFromFiles("tex/Day", ".png");
    marrow::Texture night = marrow::Texture::loadCubeFromFiles("tex/Night", ".png");
    marrow::Skybox skybox(&day, &night, &light, &light2, 30.0f);
    marrow::Renderer renderer;
    renderer.addObject(&cabob);
    renderer.addObject(&cabob2);
    renderer.addObject(&cabob3);
    renderer.addObject(&house);
    renderer.addLight(&light);
    renderer.addLight(&light2);
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
