#include "renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>

namespace marrow {
    Renderer::Renderer() : _objectList(), _lightList() {
        //_terrain_shader = TerrainShader();
        _object_shader = ObjectShader();
        _projectionMatrix = glm::perspective(glm::radians(45.0f), float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT)), 0.1f, 1000.0f);
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

    void Renderer::render(Camera & camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _object_shader.set();
        _object_shader.setFog(_fogColor, _fogDensity);
        _object_shader.setLights(_lightList);
        _object_shader.setEyePos(camera.getEyePosition());
        glm::mat4 pv_matrix = _projectionMatrix * camera.getViewMatrix();
        glm::mat4 def_mod_matrix = glm::mat4(1.0f);
        for(auto i: _objectList) {
            i->draw(&_object_shader, pv_matrix, def_mod_matrix);
        }
        _object_shader.unset();
    }
}
