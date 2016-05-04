#include "window.hpp"
#include "initialiser.hpp"
#include "light.hpp"
#include "renderer.hpp"

#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int main(int argc, char ** argv) {
    marrow::Initialiser::init(argc, argv);
    marrow::Window window(500, 500, "Legolas");
    marrow::Camera camera(glm::vec3(10.0f, 2.0f, 0.0f), glm::vec3(-1.0f, 0.1f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    marrow::Geometry cabinet("obj/plant.obj");
    marrow::Texture plantex("tex/pino.png");
    marrow::Object cabob(&cabinet, &plantex, glm::mat4(1.0));
    marrow::Light light(glm::vec4(10.0f, 12.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(3.4f, 0.0f, 0.0f));
    marrow::Renderer renderer;
    renderer.addObject(&cabob);
    renderer.addLight(&light);
    renderer.render(camera);
    glutSwapBuffers();
    glutMainLoop();
    return 0;
}
