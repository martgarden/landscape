#ifndef MARROW_LIGHT_H
#define MARROW_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace marrow {
    class Light {
        private:
            GLuint _ubo_id;
            struct _ubo_structure {
                GLfloat _position[4];
                GLfloat _diffuse[4];
                GLfloat _ambient[4];
                GLfloat _specular[4];
            } _ubo_data;

        public:
            Light(glm::vec4 & position, glm::vec3 & diffuse, glm::vec3 & ambient, glm::vec3 & specular);

            GLuint getUBO();

    };

    extern Light NO_LIGHT;
}

#endif
