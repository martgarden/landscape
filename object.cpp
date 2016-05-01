#include "object.hpp"

namespace marrow {
    Object(Geometry * model, glm::mat4 model_matrix) {
        _model = model;
        _model_matrix = model_matrix;
    }

    void Object::draw(ObjectShader * shader, glm::mat4 model_matrix) {
        glm::mat4 new_model_matrix = model_matrix * _model_matrix;
        if(_model != NULL) {
            shader->setModelMatrix(new_model_matrix);
            shader->setNormalMatrix(glm::inverse(glm::transpose(new_model_matrix)));
            _model->draw();
        }
        for(auto i : subnodes) {
            i->draw(shader, new_model_matrix);
        }
    }

}
