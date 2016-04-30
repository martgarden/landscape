#include "objectShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    ObjectShader::ObjectShader() {
        createAndLinkProgram("object_vertex.glsl", "object_fragment.glsl");
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
        _eye_pos_loc = getUniformLocation("eye_pos");
        _light_data_bloc = getUniformBlockIndex("light_data");
    }

    void ObjectShader::setModelMatrix(glm::mat4 & model_matrix) {
        glUniformMatrix4fv(_model_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
    }

    void ObjectShader::setPVMMatrix(glm::mat4 & pvm_matrix) {
        glUniformMatrix4fv(_pvm_matrix_loc, 1, GL_FALSE, glm::value_ptr(pvm_matrix));
    }

    void ObjectShader::setFog(glm::vec3 & fog_color, float fog_density) {
        glUniform3fv(_fog_color_loc, 1, glm::value_ptr(fog_color));
        glUniform1f(_fog_density_loc, fog_density);
    }

    void ObjectShader::setEyePos(glm::vec4 & eye_pos) {
        glUniform4fv(_eye_pos_loc, 1, glm::value_ptr(eye_pos));
    }

    void ObjectShader::setLights(std::list<Light *> & lights) {
        auto it = lights.begin();
        for(int i = 0; i < MAX_LIGHTS; i++) {
            if(it == lights.end())
                glBindBufferBase(GL_UNIFORM_BUFFER, _light_data_bloc + i, NO_LIGHT.getUBO());
            else {
                glBindBufferBase(GL_UNIFORM_BUFFER, _light_data_bloc + i, (*it)->getUBO());
                it++;
            }
        }
    }

}
