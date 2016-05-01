#ifndef MARROW_CAMERA_H
#define MARROW_CAMERA_H

#include <glm/glm.hpp>

namespace marrow {
    class Camera {
        protected:
            glm::vec3 _eye_position;
            glm::vec3 _direction;
            glm::vec3 _normal;

        public:
            Camera(glm::vec3 eye_position, glm::vec3 direction, glm::vec3 normal);

            glm::vec3 getEyePosition();
            glm::mat4 getViewMatrix();

    };
}

#endif
