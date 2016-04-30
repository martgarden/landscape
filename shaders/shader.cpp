#include "shader.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace marrow {

    string LoadFileToString(const char *file_name)
    {
        ifstream file(file_name);
        stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    GLuint Shader::loadAndCompileShader(GLenum shader_type, const char *file_name)
    {
        // Load the file from the disk
        string s_source = LoadFileToString(file_name);
        if (s_source.empty())
        {
            cout << "File " << file_name << " is empty or failed to load" << endl;
            return 0;
        }

        // Create shader object and set the source
        GLuint shader = glCreateShader(shader_type);
        const char *source = s_source.c_str();
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // Compile and get errors
        int compile_status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
        if (GL_FALSE == compile_status)
        {
            switch (shader_type)
            {
            case GL_VERTEX_SHADER:            cout << "Failed to compile vertex shader " << file_name << endl;                    break;
            case GL_FRAGMENT_SHADER:        cout << "Failed to compile fragment shader " << file_name << endl;                    break;
            case GL_GEOMETRY_SHADER:        cout << "Failed to compile geometry shader " << file_name << endl;                    break;
            case GL_TESS_CONTROL_SHADER:    cout << "Failed to compile tessellation control shader " << file_name << endl;        break;
            case GL_TESS_EVALUATION_SHADER:    cout << "Failed to compile tessellation evaluation shader " << file_name << endl;    break;
            default:                        cout << "Failed to compile shader " << file_name << endl;                            break;
            }

            int log_len = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
            unique_ptr<char []> log(new char[log_len]);
            glGetShaderInfoLog(shader, log_len, nullptr, log.get());
            cout << log.get() << endl;

            glDeleteShader(shader);
            return 0;
        }
        else return shader;
    }

    void Shader::createAndLinkProgram(const char * vertex_shader_file, const char * fragment_shader_file) {
        GLuint vs_shader = loadAndCompileShader(GL_VERTEX_SHADER, vertex_shader_file);
        if (0 == vs_shader) {
            return;
        }
        GLuint fs_shader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragment_shader_file);
        if (0 == fs_shader) {
            glDeleteShader(vs_shader);
            return;
        }

        GLuint program = glCreateProgram();
        glAttachShader(program, vs_shader);
        glAttachShader(program, fs_shader);
        glLinkProgram(program);

        int link_status;
        glGetProgramiv(program, GL_LINK_STATUS, &link_status);
        if (GL_FALSE == link_status) {
            cout << "Failed to link program with vertex shader " << vertex_shader_file << " and fragment shader " << fragment_shader_file << endl;
            int log_len = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
            unique_ptr<char []> log(new char[log_len]);
            glGetProgramInfoLog(program, log_len, nullptr, log.get());
            cout << log.get() << endl;
            glDeleteShader(vs_shader);
            glDeleteShader(fs_shader);
            glDeleteProgram(program);
            return;
        }
        else _program_id = program;
    }

    void Shader::setInLocation(int index, const char * in_name) {
        if(_program_id == 0)
            return;
        glBindAttribLocation(_program_id, index, in_name);
    }

    int Shader::getUniformLocation(const char * uniform_name) {
        if(_program_id == 0)
            return -1;
        return glGetUniformLocation(_program_id, uniform_name);
    }

    int Shader::getUniformBlockIndex(const char * uniform_block_name) {
        if(_program_id == 0)
            return -1;
        return glGetUniformBlockIndex(_program_id, uniform_block_name);
    }

    void Shader::set() {
        glUseProgram(_program_id);
    }

    void Shader::unset() {
        glUseProgram(0);
    }
}
