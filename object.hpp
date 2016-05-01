#ifndef MARROW_OBJECT_H
#define MARROW_OBJECT_H

#include "geometry.hpp"
#include "shaders/objectShader.hpp"

#include <list>

namespace marrow {
    class Object {
        protected:
            Geometry * _model;
            //Texture * _texture;
            glm::mat4 _model_matrix;

            std::list<Object *> _subnodes;

        public:
            Object(Geometry * model, glm::mat4 model_matrix);

            void draw(ObjectShader * shader, glm::mat4 & pv_matrix, glm::mat4 & model_matrix);

    };
}

#endif
