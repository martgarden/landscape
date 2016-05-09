#ifndef MARROW_RENDERER_H
#define MARROW_RENDERER_H

#include "camera.hpp"
#include "shaders/objectShader.hpp"
#include "shaders/terrainShader.hpp"
#include "shaders/skyboxShader.hpp"
#include "object.hpp"
#include "terrain.hpp"
#include "skybox.hpp"

#include <list>
#include <map>

namespace marrow {
    class Renderer {
        private:
            const glm::vec3 _fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
            const float _fogDensity = 0.1;
            TerrainShader _terrain_shader;
            ObjectShader _object_shader;
            SkyboxShader _skybox_shader;
            glm::mat4 _projectionMatrix;
            std::list<Object *> _objectList;
            std::list<Light *> _lightList;
            std::map<std::pair<GLint, GLint>, Terrain * > _terrainList;
            Skybox * _skybox = NULL;

        public:
            Renderer();

            void addObject(Object * newObject);
            void addLight(Light * newLight);
            void addTerrain(std::pair<GLint, GLint> offset, Terrain * newTerrain);
            void setSkybox(Skybox * skybox);
            void render(Camera & camera);
    };
}

#endif
