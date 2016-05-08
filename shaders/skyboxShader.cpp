#include "skyboxShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    SkyboxShader::SkyboxShader() {
        createAndLinkProgram("shaders/skybox_vertex.glsl", "shaders/skybox_fragment.glsl");
        //uniform
        _pv_matrix_loc = getUniformLocation("pv_matrix");
        _day_tex_loc = getUniformLocation("day_tex");
        _night_tex_loc = getUniformLocation("night_tex");
        _sun_pos_loc = getUniformLocation("sun_pos");
        _sun_color_loc = getUniformLocation("sun_color");
        _moon_color_loc = getUniformLocation("moon_color");
    }

    void SkyboxShader::setPVMatrix(glm::mat4 pv_matrix) {
        glUniformMatrix4fv(_pv_matrix_loc, 1, GL_FALSE, glm::value_ptr(pv_matrix));
    }

    void SkyboxShader::setDayTex(GLint slot) {
        glUniform1i(_day_tex_loc, slot);
    }

    void SkyboxShader::setNightTex(GLint slot) {
        glUniform1i(_night_tex_loc, slot);
    }

    void SkyboxShader::setSunPosition(const glm::vec3 & sun_position) {
        glUniform3fv(_sun_pos_loc, 1, glm::value_ptr(sun_position));
    }

    void SkyboxShader::setSunColor(const glm::vec3 & sun_color) {
        glUniform3fv(_sun_color_loc, 1, glm::value_ptr(sun_color));
    }

    void SkyboxShader::setMoonColor(const glm::vec3 & moon_color) {
        glUniform3fv(_moon_color_loc, 1, glm::value_ptr(moon_color));
    }

}
