#ifndef MARROW_WATER_H
#define MARROW_WATER_H

#include "geometry.hpp"

#include <set>

namespace marrow {
    class Water {
        private:
            Geometry * _model;
            std::set<std::pair<int, int> > _covered_terrains;

        public:
            Water(float max_x, float max_z, float x_res, float z_res);

            void draw();
            std::set<std::pair<int, int> > * getTerrains();
    };
}

#endif
