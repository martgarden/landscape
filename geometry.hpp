#ifndef MARROW_GEOMETRY_H
#define MARROW_GEOMETRY_H

namespace marrow {
    class Geometry {
        private:
        GLuint VertexBuffers[3];
        GLuint IndexBuffer;
        GLuint VAO;
        GLenum Mode;
        GLsizei DrawArraysCount;
        GLsizei DrawElementsCount;

        bool parseOBJ(const char *file_name, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, std::vector<glm::vec2> &out_tex_coords, std::vector<GLushort> &out_indices);

    public:
        Geometry();
        Geometry(const Geometry &rhs);
        Geometry &operator =(const Geometry &rhs);
        Geometry(const char * file_name);

        static Geometry loadOBJ(const char * file_name);

    };
}

#endif
