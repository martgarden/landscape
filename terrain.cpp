#include "terrain.hpp"

#include <iostream>

namespace marrow {
    Geometry * Terrain::_model = NULL;

    Terrain::Terrain(Texture * height_map, Texture * background_texture) {
        if(_model == NULL) {
            float vertices[SIZE*SIZE*2];
            float * it = vertices;
            for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                    *it = float(j) / SIZE;
                    it++;
                    *it = float(i) / SIZE;
                    it++;
                }
            }
            GLushort indices[(SIZE-1)*(SIZE-1)*6];
            GLushort * it2 = indices;
            for(int i = 0; i < SIZE - 1; i++) {
                for(int j = 0; j < SIZE - 1; j++) {
                    *it2 = SIZE*i + j;
                    *(it2+1) = SIZE*(i+1) + j + 1;
                    *(it2+2) = SIZE*i + j + 1;
                    *(it2+3) = SIZE*i + j;
                    *(it2+4) = SIZE*(i+1) + j;
                    *(it2+5) = SIZE*(i+1) + j + 1;
                    it2 += 6;
                }
            }
            _model = new Geometry(vertices, SIZE*SIZE*2, indices, (SIZE-1)*(SIZE-1)*6);
        }
        _height_map = height_map;
        _height_map->setClamp();
        _background_texture = background_texture;
        _background_texture->setRepeat();
    }

    void Terrain::draw(TerrainShader * shader) {
        shader->setHeightMap(0);
        glActiveTexture(GL_TEXTURE0);
        _height_map->set();
        shader->setBackgroundTex(1);
        glActiveTexture(GL_TEXTURE1);
        _background_texture->set();
        _model->draw();
        _height_map->unset();
    }
}
