#include "waterShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    WaterShader::WaterShader() {
        createAndLinkProgram("shaders/water_vertex.glsl", "shaders/water_fragment.glsl");
        //uniform
        _water_level_loc = getUniformLocation("water_level");
        _pv_matrix_loc = getUniformLocation("pv_matrix");
        _fog_color_loc = getUniformLocation("fog_color");
        _fog_density_loc = getUniformLocation("fog_density");
        _eye_pos_loc = getUniformLocation("eye_position");
        _reflect_tex_loc = getUniformLocation("reflect_tex");
        _refract_tex_loc = getUniformLocation("refract_tex");
        _no_lights_loc = getUniformLocation("no_lights");
        _light_indices_loc = getUniformLocation("light_indices");
        _light_ubo_bloc = getUniformBlockIndex("light_ubo");
    }

    void WaterShader::setWaterLevel(float water_level) {
        glUniform1f(_water_level_loc, water_level);
    }

    void WaterShader::setPVMatrix(glm::mat4 pv_matrix) {
        glUniformMatrix4fv(_pv_matrix_loc, 1, GL_FALSE, glm::value_ptr(pv_matrix));
    }

    void WaterShader::setFog(const glm::vec3 & fog_color, const float fog_density) {
        glUniform3fv(_fog_color_loc, 1, glm::value_ptr(fog_color));
        glUniform1f(_fog_density_loc, fog_density);
    }

    void WaterShader::setEyePos(const glm::vec3 & eye_pos) {
        glUniform3fv(_eye_pos_loc, 1, glm::value_ptr(eye_pos));
    }

    void WaterShader::setReflectTex(GLint slot) {
        glUniform1i(_reflect_tex_loc, slot);
    }

    void WaterShader::setRefractTex(GLint slot) {
        glUniform1i(_refract_tex_loc, slot);
    }

    void WaterShader::setLights(std::list<Light *> & lights) {
        glBindBufferBase(GL_UNIFORM_BUFFER, _light_ubo_bloc, Light::getUBO());
        glUniform1i(_no_lights_loc, lights.size());
        GLint lights_i[20];
        int i = 0;
        for(auto it: lights) {
            lights_i[i] = it->getArrayPosition();
            i++;
        }
        glUniform1iv(_light_indices_loc, lights.size(), lights_i);
    }

}
