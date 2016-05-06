#include "window.hpp"

#include "initialiser.hpp"

namespace marrow {
    SDL_Window * Window::_current_window = NULL;

    Window::Window() {;}

    Window::Window(int width, int height, std::string title) {
        Initialiser::init();
        _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
        _context = SDL_GL_CreateContext(_window);
        _current_window = _window;
        Initialiser::afterInit();
    }

    SDL_Window * Window::getCurrentWindow() {
        return _current_window;
    }

    void Window::swap() {
        SDL_GL_SwapWindow(_current_window);
    }

    Window::~Window() {
        SDL_GL_DeleteContext(_context);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }
}
