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
            int _normal_matrix_loc = -1;
            int _pvm_matrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _light_data_bloc = -1;
            static const int MAX_LIGHTS = 4;

        public:
            static const int _normal_loc = 1;
            static const int _tex_coord_loc = 2;

            ObjectShader();

            void setNormalMatrix(glm::mat4 normal_matrix);
            void setPVMMatrix(glm::mat4 pvm_matrix);
            void setFog(const glm::vec3 & fog_color, const float fog_density);
            void setEyePos(const glm::vec3 & eye_pos);
            void setLights(std::list<Light *> & lights);

    };
}

#endif
