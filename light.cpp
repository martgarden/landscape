#include "light.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    GLuint Light::_ubo_id = GL_INVALID_INDEX;
    int Light::_last_used = -1;
    Light::_ubo_structure Light::_ubo_data[MAX_LIGHTS] = {0};

    Light::Light(glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 attenuation) {
        if(_ubo_id == GL_INVALID_INDEX) {
            glGenBuffers(1, &_ubo_id);
            glBindBuffer(GL_UNIFORM_BUFFER, _ubo_id);
            glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS*sizeof(_ubo_structure), NULL, GL_STATIC_DRAW);
        }
        if(_last_used == MAX_LIGHTS)
            return;
        _array_position = _last_used + 1;
        _last_used++;
        memcpy(_ubo_data[_array_position]._attenuation, glm::value_ptr(attenuation), sizeof(GLfloat)*3);
        setParams(position, ambient, diffuse, specular);
    }

    void Light::update() {
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo_id);
        glBufferSubData(GL_UNIFORM_BUFFER, _array_position*sizeof(_ubo_structure), sizeof(_ubo_structure), _ubo_data + _array_position);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void Light::setParams(glm::vec4 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
        memcpy(_ubo_data[_array_position]._position, glm::value_ptr(position), sizeof(GLfloat)*4);
        memcpy(_ubo_data[_array_position]._diffuse, glm::value_ptr(diffuse), sizeof(GLfloat)*3);
        memcpy(_ubo_data[_array_position]._ambient, glm::value_ptr(ambient), sizeof(GLfloat)*3);
        memcpy(_ubo_data[_array_position]._specular, glm::value_ptr(specular), sizeof(GLfloat)*3);
        update();
    }

    void Light::setPosition(glm::vec4 position) {
        memcpy(_ubo_data[_array_position]._position, glm::value_ptr(position), sizeof(GLfloat)*4);
        update();
    }

    int Light::getArrayPosition() {
        return _array_position;
    }

    glm::vec4 Light::getPosition() {
        return glm::vec4(_ubo_data[_array_position]._position[0],
                         _ubo_data[_array_position]._position[1],
                         _ubo_data[_array_position]._position[2],
                         _ubo_data[_array_position]._position[3]);
    }

    GLuint Light::getUBO() {
        return _ubo_id;
    }
}
