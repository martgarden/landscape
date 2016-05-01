#include "window.hpp"
#include "initialiser.hpp"
#include "light.hpp"
#include "renderer.hpp"

#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

marrow::Light * marrow::NO_LIGHT;

int main(int argc, char ** argv) {
    marrow::Initialiser::init(argc, argv);
    marrow::Window window(500, 500, "Legolas");
    marrow::NO_LIGHT = new marrow::Light(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    marrow::Camera camera(glm::vec3(25.0f, 5.0f, 0.0f), glm::vec3(-1.0f, -0.3f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    marrow::Geometry cabinet("obj/cabinet.obj");
    marrow::Object cabob(&cabinet, glm::rotate(glm::mat4(1.0), -0.1f, glm::vec3(1.0, 0.0, 0.0)));
    marrow::Light light(glm::vec4(1.0f, 4.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.4f, 0.4f, 0.4f));
    marrow::Renderer renderer;
    renderer.addObject(&cabob);
    renderer.addLight(&light);
    renderer.render(camera);
    glutSwapBuffers();
    glutMainLoop();
    return 0;
}
