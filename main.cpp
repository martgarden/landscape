#include "window.hpp"
#include "initialiser.hpp"
#include "light.hpp"
#include "renderer.hpp"

#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

marrow::Camera * camera;
marrow::Renderer * renderer;

void key_pressed(unsigned char key, int mouseX, int mouseY)
{
    switch (key)
    {
        case 27:        // VK_ESCAPE
            exit(0);
            break;
        case 'l':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutPostRedisplay();
            break;
        case 'f':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glutPostRedisplay();
            break;
        case 't':
            glutFullScreenToggle();
            break;
        case 'a':
            camera->left(1);
            glutPostRedisplay();
            break;
        case 'd':
            camera->right(1);
            glutPostRedisplay();
            break;
        case 'w':
            camera->up(1);
            glutPostRedisplay();
            break;
        case 's':
            camera->down(1);
            glutPostRedisplay();
            break;
    }
}

void render() {
    renderer->render(*camera);
    glutSwapBuffers();
}

int main(int argc, char ** argv) {
    marrow::Initialiser::init(argc, argv);
    marrow::Window window(500, 500, "Legolas");
    camera = new marrow::Camera(glm::vec3(0.0f, 0.0f, -10.0f), 0, 0);
    marrow::Geometry cabinet("obj/plant.obj");
    marrow::Texture plantex("tex/pino.png");
    marrow::Object cabob(&cabinet, &plantex, glm::mat4(1.0));
    marrow::Object cabob2(&cabinet, &plantex, glm::translate(glm::mat4(1.0), glm::vec3(3.0, 0.0, 1.0)));
    marrow::Light light(glm::vec4(10.0f, 12.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(3.4f, 0.0f, 0.0f));
    renderer = new marrow::Renderer;
    renderer->addObject(&cabob);
    renderer->addObject(&cabob2);
    renderer->addLight(&light);
    renderer->render(*camera);
    glutSwapBuffers();
    glutKeyboardFunc(key_pressed);
    glutDisplayFunc(render);
    glutMainLoop();
    return 0;
}
