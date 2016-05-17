#include "skybox.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace marrow {
    Geometry * Skybox::_model = NULL;

    Skybox::Skybox(Texture * day_tex, Texture * night_tex, Light * sun_light, Light * moon_light, float start_time) {
        if(_model == NULL) {
            std::cerr<<"a";
            float vertices[] = {
                -1.0, -1.0, -1.0,
                -1.0, -1.0,  1.0,
                 1.0, -1.0,  1.0,
                 1.0, -1.0, -1.0,
                -1.0,  1.0, -1.0,
                -1.0,  1.0,  1.0,
                 1.0,  1.0,  1.0,
                 1.0,  1.0, -1.0
            };
            GLushort indices[] = {
                0, 1, 2,
                0, 2, 3,
                0, 5, 1,
                0, 4, 5,
                1, 6, 2,
                1, 5, 6,
                2, 7, 3,
                2, 6, 7,
                3, 4, 0,
                3, 7, 4,
                4, 6, 5,
                4, 7, 6
            };
            _model = new Geometry(vertices, 24, 3, indices, 36);
        }
        _day_tex = day_tex;
        _night_tex = night_tex;
        _sun_light = sun_light;
        _moon_light = moon_light;
        _day_time = start_time;
    }

    void Skybox::tick(float span) {
        _day_time += span;
        if(_day_time > DAY)
            _day_time -= DAY;
        _sun_vec = glm::rotate(glm::mat4(1.0), (_day_time/DAY)*6.283f, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        _sun_vec.w = 0.0f;
        float rdt = _day_time;
        if(_day_time > DAY/2.0f)
            rdt = DAY - _day_time;
        rdt = rdt*(24.0f/DAY); //hours
        //sun
        if(rdt < 5.0f)
            _sun_color = (1-(rdt/5.0f))*glm::vec3(1.0, 1.0, 0.5) + (rdt/5.0f)*glm::vec3(1.0, 0.2, 0.05);
        else if(rdt < 7.0f)
            _sun_color = (1-((rdt-5.0f)/2.0f))*glm::vec3(1.0, 0.2, 0.05) + ((rdt-5.0f)/2.0f)*glm::vec3(0.1, 0.0, 0.45);
        else if(rdt < 7.5f)
            _sun_color = (1-((rdt-7.0f)/0.5f))*glm::vec3(0.1, 0.0, 0.45) + ((rdt-7.0f)/0.5f)*glm::vec3(0.0, 0.0, 0.0);
        else
            _sun_color = glm::vec3(0.0, 0.0, 0.0);
        _sun_light->setParams(_sun_vec, _sun_color*0.2f, _sun_color*0.6f, _sun_color + glm::vec3(1.0, 1.0, 1.0));
        //moon
        if(rdt > 8.0f)
            _moon_color = glm::vec3(1.0, 1.0, 1.0);
        else if(rdt > 6.0f)
            _moon_color = ((rdt-6.0f)/2.0f)*glm::vec3(1.0, 1.0, 1.0);
        else
            _moon_color = glm::vec3(0.0, 0.0, 0.0);
        _moon_light->setParams(-_sun_vec, _moon_color*0.05f, _moon_color*0.2f, _moon_color);
    }

    void Skybox::draw(SkyboxShader * shader, glm::mat4 view_matrix, glm::mat4 projection_matrix) {
        shader->setSunPosition(glm::vec3(_sun_vec));
        shader->setSunColor(_sun_color);
        shader->setMoonColor(_moon_color);
        shader->setDayTex(0);
        glActiveTexture(GL_TEXTURE0);
        _day_tex->set();
        shader->setNightTex(1);
        glActiveTexture(GL_TEXTURE1);
        _night_tex->set();
        float * it = ((float*)(glm::value_ptr(view_matrix))+12);
        *it = 0.0f;
        it++;
        *it = 0.0f;
        it++;
        *it = 0.0f;
        shader->setPVMatrix(projection_matrix * view_matrix);
        _model->draw();
        _day_tex->unset();
    }

    float Skybox::getDayTime() {
        return _day_time;
    }
}
