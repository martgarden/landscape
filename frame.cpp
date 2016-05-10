#include "frame.hpp"

#include <iostream>

namespace marrow {
    Frame::Frame(int width, int height) {
        _w = width;
        _h = height;
        GLuint color_texture, depth_texture;
        glGenTextures(1, &color_texture);
        glGenTextures(1, &depth_texture);
        glBindTexture(GL_TEXTURE_2D, color_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, depth_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _w, _h, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        glGenFramebuffers(1, &_fbo_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);
        GLenum drawbufs[1] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawbufs);
        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Failed to create a complete framebuffer" << std::endl;
            return;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        _color_texture = new Texture(color_texture, GL_TEXTURE_2D);
        _depth_texture = new Texture(depth_texture, GL_TEXTURE_2D);
    }

    void Frame::set() {
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
        glViewport(0, 0, _w, _h);
    }

    void Frame::unset() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Texture * Frame::getColorTex() {
        return _color_texture;
    }

    Texture * Frame::getDepthTex() {
        return _depth_texture;
    }
}
