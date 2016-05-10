#ifndef MARROW_WATER_H
#define MARROW_WATER_H

#include "geometry.hpp"

namespace marrow {
    class Water {
        private:
            Geometry * _model;

        public:
            Water(float max_x, float max_z, float x_res, float z_res);

            void draw();
    };
}

#endif
