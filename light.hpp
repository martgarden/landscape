#ifndef MARROW_LIGHT_H
#define MARROW_LIGHT_H

namespace marrow {
    class Light {
        private:
            struct _ubo_structure {
                float _position[4];
                float _diffuse[4];
                float _ambient[4];
                float _specular[4];
            } _ubo_data;
            Gluint _ubo_id;

        public:
            Light(glm::vec4 position, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular);

            getUBO();

    };
}

#endif
