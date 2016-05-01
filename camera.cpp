#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace marrow {
    Camera::Camera(glm::vec3 eye_position, glm::vec3 direction, glm::vec3 normal) {
        _eye_position = eye_position;
        _direction = direction;
        _normal = normal;
    }

    glm::vec3 Camera::getEyePosition() {
        return _eye_position;
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(_eye_position, _eye_position + _direction, _normal);
    }
}
