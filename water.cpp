#include "water.hpp"

namespace marrow {
    Water::Water(float max_x, float max_z, float x_res, float z_res) {
        float vertices[8] = {
            max_x, max_z,
            max_x - x_res, max_z,
            max_x, max_z - z_res,
            max_x - x_res, max_z - z_res
        };
        GLushort indices[6] = {
            0, 1, 3,
            0, 3, 2
        };
        _model = new Geometry(vertices, 8, 2, indices, 6);
    }

    void Water::draw() {
        _model->draw();
    }
}
