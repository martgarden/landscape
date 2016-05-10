#ifndef MARROW_FRAME_H
#define MARROW_FRAME_H

#include "texture.hpp"

namespace marrow {
    class Frame {
        private:
            GLuint _fbo_id;
            Texture * _color_texture;
            Texture * _depth_texture;
            int _w, _h;

        public:
            Frame(int width, int height);

            void set();
            void unset();
            Texture * getColorTex();
            Texture * getDepthTex();
    };
}

#endif
