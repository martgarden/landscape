#ifndef MARROW_WINDOW_H
#define MARROW_WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace marrow {
    class Window {
        private:
            SDL_Window * _window;
            SDL_GLContext _context;
            static SDL_Window * _current_window;

        public:
            Window();

            Window(int width, int height, std::string title);

            static SDL_Window * getCurrentWindow();
            static void swap();

            ~Window();
    };
}

#endif
