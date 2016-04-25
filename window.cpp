#include "window.hpp"

#include "initialiser.hpp"

#include <GL/freeglut.h>

namespace marrow {

    Window::Window() {;}

    Window::Window(int width, int height, std::string title) {
        //Initialiser::init();
        glutInitWindowSize(width, height);
        _identifier = glutCreateWindow(title.c_str());
        Initialiser::afterInit();
    }

    void Window::SetFocus() {
        glutSetWindow(_identifier);
    }

    Window::~Window() {;}

}
