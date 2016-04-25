#ifndef MARROW_SHADER_H
#define MARROW_SHADER_H

namespace marrow {
    class Shader {
        private:
            int _position_loc = -1;
            GLuint _program_id = 0;

            string LoadFileToString(const char * file_name);
            GLuint loadAndCompileShader(GLenum shader_type, const char * file_name);
            void createAndLinkProgram(const char * vertex_shader_file, const char * fragment_shader_file);
            int getInLocation(const char * in_name);
            int getUniformLocation(const char * uniform_name);

    };
}

#endif
