#include "object.hpp"

namespace marrow {
    Object::Object(Geometry * model, glm::mat4 model_matrix) {
        _model = model;
        _model_matrix = model_matrix;
    }

    void Object::draw(ObjectShader * shader, glm::mat4 & pv_matrix, glm::mat4 & model_matrix) {
        glm::mat4 new_model_matrix = model_matrix * _model_matrix;
        if(_model != NULL) {
            shader->setModelMatrix(new_model_matrix);
            shader->setNormalMatrix(glm::inverse(glm::transpose(glm::mat3(new_model_matrix))));
            shader->setPVMMatrix(pv_matrix * new_model_matrix);
            _model->draw();
        }
        for(auto i : _subnodes) {
            i->draw(shader, pv_matrix, new_model_matrix);
        }
    }

}
