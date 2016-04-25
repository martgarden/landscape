#include "window.hpp"
#include "initialiser.hpp"

#include <GL/freeglut.h>

int main(int argc, char ** argv) {
    marrow::Initialiser::init(argc, argv);
    marrow::Window window(500, 500, "Legolas");
    glutMainLoop();
    return 0;
}
