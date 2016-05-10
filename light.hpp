#ifndef MARROW_LIGHT_H
#define MARROW_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace marrow {
    class Light {
        private:
            static const int MAX_LIGHTS = 20;
            struct _ubo_structure {
                GLfloat _position[4];
                GLfloat _ambient[4];
                GLfloat _diffuse[4];
                GLfloat _specular[4];
                GLfloat _attenuation[4];
            };
            static GLuint _ubo_id;
            static _ubo_structure _ubo_data[MAX_LIGHTS];
            static int _last_used;
            int _array_position;

        public:

            Light(glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 attenuation);

            void update();
            void setParams(glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
            void setPosition(glm::vec4 position);
            int getArrayPosition();
            static GLuint getUBO();

    };
}

#endif
