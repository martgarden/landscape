#include "light.hpp"

namespace marrow {
    Light::Light(glm::vec4 & position, glm::vec3 & diffuse, glm::vec3 & ambient, glm::vec3 & specular) {
        glGenBuffers(1, &_ubo_id);
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo_id);
        memcpy(_ubo_data.position, glm::value_ptr(position), sizeof(GLfloat)*4);
        memcpy(_ubo_data.diffuse, glm::value_ptr(diffuse), sizeof(GLfloat)*3);
        memcpy(_ubo_data.amibient, glm::value_ptr(amibient), sizeof(GLfloat)*3);
        memcpy(_ubo_data.specular, glm::value_ptr(specular), sizeof(GLfloat)*3);
        glBufferData(GL_UNIFORM_BUFFER, 16*sizeof(GLfloat), &_ubo_data, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    Gluint Light::getUBO() {
        return _ubo_id;
    }
}
