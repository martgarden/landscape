#ifndef MARROW_CAMERA_H
#define MARROW_CAMERA_H

#include <glm/glm.hpp>

namespace marrow {
    class Camera {
        protected:
            glm::vec3 _eye_position;
            float _rotation;
            float _elevation;
            const float _rotation_speed = 0.05f;
            glm::vec3 _direction;
            glm::vec3 _normal;

            void update();

        public:
            Camera(glm::vec3 eye_position, glm::vec3 direction, glm::vec3 normal);
            Camera(glm::vec3 eye_position, float rotation, float elevation);

            glm::vec3 getEyePosition();
            glm::mat4 getViewMatrix();
            void left(float time);
            void right(float time);
            void up(float time);
            void down(float time);

    };
}

#endif
