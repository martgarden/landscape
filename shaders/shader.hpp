#ifndef MARROW_SHADER_H
#define MARROW_SHADER_H

#include <GL/glew.h>

namespace marrow {
    class Shader {
        protected:
            GLuint _program_id = 0;

            GLuint loadAndCompileShader(GLenum shader_type, const char * file_name);
            void createAndLinkProgram(const char * vertex_shader_file, const char * fragment_shader_file);
            int getUniformLocation(const char * uniform_name);
            int getUniformBlockIndex(const char * uniform_block_name);

        public:
            static const int _position_loc = 0;
            static const int _normal_loc = 1;
            static const int _tex_coord_loc = 2;

            void set();
            static void unset();

    };
}

#endif
