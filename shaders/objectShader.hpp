#ifndef MARROW_OBJECTSHADER_H
#define MARROW_OBJECTSHADER_H

#include "shader.hpp"
#include "../light.hpp"

#include <glm/glm.hpp>

#include <list>

namespace marrow {
    class ObjectShader : public Shader {
        private:
            //uniform
            int _model_matrix_loc = -1;
            int _normal_matrix_loc = -1;
            int _pvm_matrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _color_tex_loc = -1;
            int _no_lights_loc = -1;
            int _light_indices_loc = -1;
            int _light_ubo_bloc = -1;

        public:
            ObjectShader();

            void setModelMatrix(glm::mat4 model_matrix);
            void setNormalMatrix(glm::mat3 normal_matrix);
            void setPVMMatrix(glm::mat4 pvm_matrix);
            void setFog(const glm::vec3 & fog_color, const float fog_density);
            void setEyePos(const glm::vec3 & eye_pos);
            void setColorTex(GLint slot);
            void setLights(std::list<Light *> & lights);

    };
}

#endif
