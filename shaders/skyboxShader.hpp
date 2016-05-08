#ifndef MARROW_SKYBOXSHADER_H
#define MARROW_SKYBOXSHADER_H

#include "shader.hpp"
#include "../light.hpp"

#include <glm/glm.hpp>

#include <list>

namespace marrow {
    class SkyboxShader : public Shader {
        private:
            //uniform
            int _pv_matrix_loc = -1;
            int _day_tex_loc = -1;
            int _night_tex_loc = -1;
            int _sun_pos_loc = -1;
            int _sun_color_loc = -1;
            int _moon_color_loc = -1;

        public:
            SkyboxShader();

            void setPVMatrix(glm::mat4 pv_matrix);
            void setDayTex(GLint slot);
            void setNightTex(GLint slot);
            void setSunPosition(const glm::vec3 & sun_position);
            void setSunColor(const glm::vec3 & sun_color);
            void setMoonColor(const glm::vec3 & moon_color);

    };
}

#endif
