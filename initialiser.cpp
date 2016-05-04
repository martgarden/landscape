#include "initialiser.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>

namespace marrow {

    bool Initialiser::_initialised = false;
    bool Initialiser::_after_initialised = false;

    Initialiser::Initialiser() {;}

    void Initialiser::init(int argc, char ** argv) {
        if(_initialised)
            return;
        // Initialize GLUT
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);        // Return from the main loop

        // Set OpenGL Context parameters
        glutInitContextVersion(3, 3);                // Use OpenGL 3.3
        glutInitContextProfile(GLUT_CORE_PROFILE);    // Use OpenGL core profile
        glutInitContextFlags(GLUT_DEBUG);            // Use OpenGL debug context
        _initialised = true;
    }

    void Initialiser::afterInit() {
        if(_after_initialised or glutGetWindow() == 0)
            return;
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        glewInit();
        // Initialize DevIL library
        ilInit();
        _after_initialised = true;
    }
}
