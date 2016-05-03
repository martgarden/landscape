#include "objectShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    ObjectShader::ObjectShader() {
        createAndLinkProgram("shaders/object_vertex.glsl", "shaders/object_fragment.glsl");
        //in
        setInLocation(_position_loc, "position");
        setInLocation(_normal_loc, "normal");
        setInLocation(_tex_coord_loc, "tex_coord");
        //uniform
        _model_matrix_loc = getUniformLocation("model_matrix");
        _normal_matrix_loc = getUniformLocation("normal_matrix");
        _pvm_matrix_loc = getUniformLocation("pvm_matrix");
        _fog_color_loc = getUniformLocation("fog_color");
        _fog_density_loc = getUniformLocation("fog_density");
        _eye_pos_loc = getUniformLocation("eye_position");
        _no_lights_loc = getUniformLocation("no_lights");
        _light_indices_loc = getUniformLocation("light_indices");
        _light_ubo_bloc = getUniformBlockIndex("light_ubo");
    }

    void ObjectShader::setModelMatrix(glm::mat4 model_matrix) {
        glUniformMatrix4fv(_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
    }

    void ObjectShader::setNormalMatrix(glm::mat3 normal_matrix) {
        glUniformMatrix3fv(_normal_matrix_loc, 1, GL_FALSE, glm::value_ptr(normal_matrix));
    }

    void ObjectShader::setPVMMatrix(glm::mat4 pvm_matrix) {
        glUniformMatrix4fv(_pvm_matrix_loc, 1, GL_FALSE, glm::value_ptr(pvm_matrix));
    }

    void ObjectShader::setFog(const glm::vec3 & fog_color, const float fog_density) {
        glUniform3fv(_fog_color_loc, 1, glm::value_ptr(fog_color));
        glUniform1f(_fog_density_loc, fog_density);
    }

    void ObjectShader::setEyePos(const glm::vec3 & eye_pos) {
        glUniform3fv(_eye_pos_loc, 1, glm::value_ptr(eye_pos));
    }

    void ObjectShader::setLights(std::list<Light *> & lights) {
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
