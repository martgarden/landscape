#include "renderer.hpp"

#include "window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

#include <iostream>

namespace marrow {
    Renderer::Renderer() : _objectList(), _lightList(), _terrainList(), _waterList() {
        SDL_GetWindowSize(Window::getCurrentWindow(), &_w, &_h);
        _projectionMatrix = glm::perspective(glm::radians(45.0f), float(_w) / float(_h), 0.1f, 610.0f);
        _frame_reflect = new Frame(_w/2, _h/2);
        _frame_refract = new Frame(_w/4, _h/4);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::addObject(Object * newObject) {
        _objectList.push_back(newObject);
    }

    void Renderer::addLight(Light * newLight) {
        _lightList.push_back(newLight);
    }

    void Renderer::addTerrain(std::pair<GLint, GLint> offset, Terrain * newTerrain) {
        _terrainList[offset] = std::make_pair(std::list<Light *>(), newTerrain);
        for(auto i: _lightList) {
            glm::vec4 position = i->getPosition();
            if(position.w == 0.0f or (position.x > offset.first*200.0f and position.x < (offset.first+1)*200.0f and position.z > offset.second*200.0f and position.z < (offset.second+1)*200.0f )) {
                _terrainList[offset].first.push_back(i);
            }
        }
    }

    void Renderer::addWater(Water * newWater) {
        _waterList.push_back(newWater);
        _swamps.insert(newWater->getTerrains()->begin(), newWater->getTerrains()->end());
    }

    void Renderer::setSkybox(Skybox * skybox) {
        _skybox = skybox;
    }

    void Renderer::setWaterLevel(float water_level) {
        _water_level = water_level;
    }

    void Renderer::basic_render(Camera & camera, glm::vec4 clip_plane, bool swamps) {
        glEnable(GL_CULL_FACE);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _object_shader.set();
        _object_shader.setClipPlane(clip_plane);
        _object_shader.setFog(_fogColor, _fogDensity);
        _object_shader.setLights(_lightList);
        _object_shader.setEyePos(camera.getEyePosition());
        glm::mat4 view_matrix = camera.getViewMatrix();
        glm::mat4 pv_matrix = _projectionMatrix * view_matrix;
        glm::mat4 def_mod_matrix = glm::mat4(1.0f);
        for(auto i: _objectList) {
            i->draw(&_object_shader, pv_matrix, def_mod_matrix);
        }
        _object_shader.unset();
        _terrain_shader.set();
        _terrain_shader.setClipPlane(clip_plane);
        _terrain_shader.setFog(_fogColor, _fogDensity);
        _terrain_shader.setEyePos(camera.getEyePosition());
        _terrain_shader.setPVMatrix(pv_matrix);
        if(swamps) {
            for(auto i: _swamps) {
                _terrain_shader.setOff(i.first, i.second);
                _terrain_shader.setLights(_terrainList[i].first);
                _terrainList[i].second->draw(&_terrain_shader);
            }
        }
        else
            for(auto i: _terrainList) {
                _terrain_shader.setOff(i.first.first, i.first.second);
                _terrain_shader.setLights(i.second.first);
                i.second.second->draw(&_terrain_shader);
            }
        _terrain_shader.unset();
        if(_skybox != NULL) {
            _skybox_shader.set();
            _skybox->draw(&_skybox_shader, view_matrix, _projectionMatrix);
            _skybox_shader.unset();
        }
    }

    void Renderer::render(Camera & camera) {
        glEnable(GL_CLIP_DISTANCE0);
        _frame_reflect->set();
        glm::vec4 plane(0.0, 1.0, 0.0, -_water_level);
        plane *= camera.mirror(_water_level);
        basic_render(camera, plane, true);
        camera.mirror(_water_level);
        _frame_reflect->unset();
        _frame_refract->set();
        basic_render(camera, -plane, true);
        _frame_refract->unset();
        glViewport(0, 0, _w, _h);
        glDisable(GL_CLIP_DISTANCE0);
        basic_render(camera, glm::vec4(0.0, 1.0, 0.0, 0.0));
        glDisable(GL_CULL_FACE);
        _water_shader.set();
        _water_shader.setFog(_fogColor, _fogDensity);
        _water_shader.setLights(_lightList);
        _water_shader.setEyePos(camera.getEyePosition());
        _water_shader.setDayTime(_skybox->getDayTime());
        glm::mat4 pv_matrix = _projectionMatrix * camera.getViewMatrix();
        _water_shader.setPVMatrix(pv_matrix);
        _water_shader.setWaterLevel(_water_level);
        _water_shader.setReflectTex(0);
        glActiveTexture(GL_TEXTURE0);
        _frame_reflect->getColorTex()->set();
        _water_shader.setRefractTex(1);
        glActiveTexture(GL_TEXTURE1);
        _frame_refract->getColorTex()->set();
        for(auto i: _waterList) {
            i->draw();
            std::cerr<<"b";
        }
    }
}
