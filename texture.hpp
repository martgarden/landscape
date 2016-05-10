#ifndef MARROW_TEXTURE_H
#define MARROW_TEXTURE_H

#include <GL/glew.h>

namespace marrow {
    class Texture {
        private:
            GLuint _tex_id = GL_INVALID_VALUE;
            GLenum _type;

        public:
            Texture();
            Texture(const char * file_name);
            Texture(GLuint tex_id, GLenum type);
            Texture &operator =(const Texture &rhs);

            static Texture loadFromFile(const char * file_name);
            static Texture loadCubeFromFiles(const char * file_prefix, const char * file_appendix);
            void set();
            void unset();
            void setRepeat();
            void setClamp();
    };
}

#endif
