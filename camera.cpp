#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace marrow {
    void Camera::update() {
        _direction = glm::mat3(glm::rotate(glm::mat4(1.0), _rotation, glm::vec3(0.0f, 1.0f, 0.0f)))*
                     glm::mat3(glm::rotate(glm::mat4(1.0), _elevation, glm::vec3(1.0f, 0.0f, 0.0f)))*
                     glm::vec3(0.0f, 0.0f, 1.0f);
    }

    Camera::Camera(glm::vec3 eye_position, glm::vec3 direction, glm::vec3 normal) {
        _eye_position = eye_position;
        _direction = direction;
        _normal = normal;
    }

    Camera::Camera(glm::vec3 eye_position, float rotation, float elevation) {
        _eye_position = eye_position;
        _normal = glm::vec3(0.0, 1.0, 0.0);
        _rotation = rotation;
        _elevation = elevation;
        update();
    }

    glm::vec3 Camera::getEyePosition() {
        return _eye_position;
    }

    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(_eye_position, _eye_position + _direction, _normal);
    }
    void Camera::left(float time) {
        _rotation -= time * _rotation_speed;
        update();
    }

    void Camera::right(float time) {
        _rotation += time * _rotation_speed;
        update();
    }

    void Camera::up(float time) {
        _elevation += time * _rotation_speed;
        update();
    }

    void Camera::down(float time) {
        _elevation -= time * _rotation_speed;
        update();
    }
}
