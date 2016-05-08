#include "renderer.hpp"

#include "window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>

namespace marrow {
    Renderer::Renderer() : _objectList(), _lightList() {
        int w, h;
        SDL_GetWindowSize(Window::getCurrentWindow(), &w, &h);
        _projectionMatrix = glm::perspective(glm::radians(45.0f), float(w) / float(h), 0.1f, 1000.0f);
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

    void Renderer::addTerrain(Terrain * newTerrain) {
        _terrain = newTerrain;
    }

    void Renderer::setSkybox(Skybox * skybox) {
        _skybox = skybox;
    }

    void Renderer::render(Camera & camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _object_shader.set();
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
        if(_terrain != NULL) {
            _terrain_shader.set();
            _terrain_shader.setFog(_fogColor, _fogDensity);
            _terrain_shader.setLights(_lightList);
            _terrain_shader.setEyePos(camera.getEyePosition());
            _terrain_shader.setPVMatrix(pv_matrix);
            _terrain->draw(&_terrain_shader);
            _terrain_shader.unset();
        }
        if(_skybox != NULL) {
            _skybox_shader.set();
            _skybox->draw(&_skybox_shader, view_matrix, _projectionMatrix);
            _skybox_shader.unset();
        }
    }
}
