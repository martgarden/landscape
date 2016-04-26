#ifndef MARROW_OBJECTSHADER_H
#define MARROW_OBJECTSHADER_H

namespace marrow {
    class ObjectShader {
        private:
            //uniform
            int _model_matrix_loc = -1;
            int _normal_matrix_loc = -1;
            int _pvmmatrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _light_data_bloc = -1;
            static const int MAX_LIGHTS = 4;

        public:
            static const int _normal_loc = 1;
            static const int _tex_coord_loc = 2;

            ObjectShader();

            void setModelMatrix(glm::mat4 & model_matrix);
            void setPVMMatrix(glm::mat4 & pvm_matrix);
            void setFog(glm::vec3 & fog_color, float fog_density);
            void setEyePos(glm::vec4 & eye_pos);
            void setLights(std::list<Light *> & lights);

    };
}

#endif
