#include "terrainShader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace marrow {
    TerrainShader::TerrainShader() {
        createAndLinkProgram("shaders/terrain_vertex.glsl", "shaders/terrain_fragment.glsl");
        //uniform
        _pv_matrix_loc = getUniformLocation("pv_matrix");
        _fog_color_loc = getUniformLocation("fog_color");
        _fog_density_loc = getUniformLocation("fog_density");
        _eye_pos_loc = getUniformLocation("eye_position");
        _x_off_loc = getUniformLocation("x_off");
        _z_off_loc = getUniformLocation("z_off");
        _height_map_loc = getUniformLocation("height_map");
        _brgb_map_loc = getUniformLocation("brgb_map");
        _background_tex_loc = getUniformLocation("background_tex");
        _red_tex_loc = getUniformLocation("red_tex");
        _green_tex_loc = getUniformLocation("green_tex");
        _blue_tex_loc = getUniformLocation("blue_tex");
        _no_lights_loc = getUniformLocation("no_lights");
        _light_indices_loc = getUniformLocation("light_indices");
        _light_ubo_bloc = getUniformBlockIndex("light_ubo");
    }

    void TerrainShader::setPVMatrix(glm::mat4 pv_matrix) {
        glUniformMatrix4fv(_pv_matrix_loc, 1, GL_FALSE, glm::value_ptr(pv_matrix));
    }

    void TerrainShader::setFog(const glm::vec3 & fog_color, const float fog_density) {
        glUniform3fv(_fog_color_loc, 1, glm::value_ptr(fog_color));
        glUniform1f(_fog_density_loc, fog_density);
    }

    void TerrainShader::setEyePos(const glm::vec3 & eye_pos) {
        glUniform3fv(_eye_pos_loc, 1, glm::value_ptr(eye_pos));
    }

    void TerrainShader::setOff(GLint x_off, GLint z_off) {
        glUniform1i(_x_off_loc, x_off);
        glUniform1i(_z_off_loc, z_off);
    }

    void TerrainShader::setHeightMap(GLint slot) {
        glUniform1i(_height_map_loc, slot);
    }

    void TerrainShader::setBRGBMap(GLint slot) {
        glUniform1i(_brgb_map_loc, slot);
    }

    void TerrainShader::setBackgroundTex(GLint slot) {
        glUniform1i(_background_tex_loc, slot);
    }

    void TerrainShader::setRedTex(GLint slot) {
        glUniform1i(_red_tex_loc, slot);
    }

    void TerrainShader::setGreenTex(GLint slot) {
        glUniform1i(_green_tex_loc, slot);
    }

    void TerrainShader::setBlueTex(GLint slot) {
        glUniform1i(_blue_tex_loc, slot);
    }

    void TerrainShader::setLights(std::list<Light *> & lights) {
        glBindBufferBase(GL_UNIFORM_BUFFER, _light_ubo_bloc, Light::getUBO());
        glUniform1i(_no_lights_loc, lights.size());
        GLint lights_i[20];
        int i = 0;
        for(auto it: lights) {
            lights_i[i] = it->getArrayPosition();
            i++;
        }
        glUniform1iv(_light_indices_loc, lights.size(), lights_i);
    }

}
