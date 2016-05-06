#ifndef MARROW_TERRAIN_H
#define MARROW_TERRAIN_H

#include "geometry.hpp"
#include "texture.hpp"
#include "shaders/terrainShader.hpp"

namespace marrow {
    class Terrain {
        private:
            const static int SIZE = 250;
            static Geometry  * _model;
            Texture * _height_map;
            Texture * _background_texture;

        public:
            Terrain(Texture * height_map, Texture * background_texture);

            void draw(TerrainShader * shader);
    };
}

#endif
