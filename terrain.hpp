#ifndef MARROW_TERRAIN_H
#define MARROW_TERRAIN_H

#include "geometry.hpp"
#include "texture.hpp"
#include "shaders/terrainShader.hpp"

namespace marrow {
    class Terrain {
        private:
            const static int SIZE = 75;
            static Geometry  * _model;
            Texture * _height_map;
            Texture * _brgb_map;
            Texture * _background_texture;
            Texture * _red_texture;
            Texture * _green_texture;
            Texture * _blue_texture;

        public:
            Terrain(Texture * height_map, Texture * brgb_map, Texture * background_texture, Texture * red_texture, Texture * green_texture, Texture * blue_texture);

            void draw(TerrainShader * shader);
    };
}

#endif
