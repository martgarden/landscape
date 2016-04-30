#ifndef MARROW_GEOMETRY_H
#define MARROW_GEOMETRY_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace marrow {
    class Geometry {
        private:
            GLuint _vertex_buffers[3];
            GLuint _index_buffer;
            GLuint _vao_id;
            GLenum _draw_mode;
            GLsizei _draw_arrays_count;
            GLsizei _draw_elemetnts_count;

            static bool parseOBJ(const char *file_name, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, std::vector<glm::vec2> &out_tex_coords, std::vector<GLushort> &out_indices);

        public:
            Geometry();
            Geometry(const Geometry &rhs);
            Geometry &operator =(const Geometry &rhs);
            Geometry(const char * file_name);

            static Geometry loadOBJ(const char * file_name);

    };
}

#endif
