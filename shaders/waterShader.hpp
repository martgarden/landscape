#ifndef MARROW_WATERSHADER_H
#define MARROW_WATERSHADER_H

#include "shader.hpp"
#include "../light.hpp"

#include <glm/glm.hpp>

#include <list>

namespace marrow {
    class WaterShader : public Shader {
        private:
            //uniform
            int _water_level_loc = -1;
            int _pv_matrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _day_time_loc = -1;
            int _reflect_tex_loc = -1;
            int _refract_tex_loc = -1;
            int _no_lights_loc = -1;
            int _light_indices_loc = -1;
            int _light_ubo_bloc = -1;

        public:
            WaterShader();

            void setWaterLevel(float water_level);
            void setPVMatrix(glm::mat4 pv_matrix);
            void setFog(const glm::vec3 & fog_color, const float fog_density);
            void setEyePos(const glm::vec3 & eye_pos);
            void setDayTime(float day_time);
            void setReflectTex(GLint slot);
            void setRefractTex(GLint slot);
            void setLights(std::list<Light *> & lights);

    };
}

#endif
