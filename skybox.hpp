#ifndef MARROW_SKYBOX_H
#define MARROW_SKYBOX_H

#include "geometry.hpp"
#include "texture.hpp"
#include "light.hpp"
#include "shaders/skyboxShader.hpp"

namespace marrow {
    class Skybox {
        private:
            static Geometry * _model;
            static constexpr float DAY = 100.0f;
            Texture * _day_tex;
            Texture * _night_tex;
            Light * _sun_light;
            Light * _moon_light;
            float _day_time;
            glm::vec4 _sun_vec;
            glm::vec3 _sun_color;
            glm::vec3 _moon_color;

        public:
            Skybox(Texture * day_tex, Texture * night_tex, Light * sun_light, Light * moon_light, float start_time = 0.0f);

            void tick(float span);
            void draw(SkyboxShader * shader, glm::mat4 view_matrix, glm::mat4 projection_matrix);
    };
}

#endif
