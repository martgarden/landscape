#include "window.hpp"
#include "initialiser.hpp"
#include "light.hpp"

#include <GL/freeglut.h>

marrow::Light * marrow::NO_LIGHT;

int main(int argc, char ** argv) {
    marrow::Initialiser::init(argc, argv);
    marrow::Window window(500, 500, "Legolas");
    marrow::NO_LIGHT = new marrow::Light(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glutMainLoop();
    return 0;
}
