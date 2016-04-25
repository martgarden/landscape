#ifndef MARROW_OBJECTSHADER_H
#define MARROW_OBJECTSHADER_H

namespace marrow {
    class ObjectShader {
        private:
            //in
            int _normal_loc = -1;
            int _tex_coord_loc = -1;
            //uniform
            int _model_matrix_loc = -1;
            int _normal_matrix_loc = -1;
            int _pv_matrix_loc = -1;
            int _fog_color_loc = -1;
            int _fog_density_loc = -1;
            int _eye_pos_loc = -1;
            int _light_data_bloc = -1;
            const int _max_lights = 4;

        public:
            ObjectShader();

            u

    };
}

#endif
