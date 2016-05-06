#include "initialiser.hpp"

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <IL/il.h>

namespace marrow {

    bool Initialiser::_initialised = false;
    bool Initialiser::_after_initialised = false;

    Initialiser::Initialiser() {;}

    void Initialiser::init() {
        if(_initialised)
            return;
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
            printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
            return;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        _initialised = true;
    }

    void Initialiser::afterInit() {
        if(_after_initialised)
            return;
        SDL_GL_SetSwapInterval(1);
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        glewInit();
        // Initialize DevIL library
        ilInit();
        _after_initialised = true;
    }
}
