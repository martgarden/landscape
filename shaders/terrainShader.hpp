#ifndef MARROW_TERRAINSHADER_H
#define MARROW_TERRAINSHADER_H

#include "shader.hpp"
#include "../light.hpp"

#include <glm/glm.hpp>

#include <list>

namespace marrow {
    class TerrainShader : public Shader {
        private:
            //uniform
            int _pv_matrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _height_map_loc = -1;
            int _background_tex_loc = -1;
            int _no_lights_loc = -1;
            int _light_indices_loc = -1;
            int _light_ubo_bloc = -1;

        public:
            TerrainShader();

            void setPVMatrix(glm::mat4 pv_matrix);
            void setFog(const glm::vec3 & fog_color, const float fog_density);
            void setEyePos(const glm::vec3 & eye_pos);
            void setHeightMap(GLint slot);
            void setBackgroundTex(GLint slot);
            void setLights(std::list<Light *> & lights);

    };
}

#endif