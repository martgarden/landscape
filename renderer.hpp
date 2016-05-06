#ifndef MARROW_RENDERER_H
#define MARROW_RENDERER_H

#include "camera.hpp"
#include "shaders/objectShader.hpp"
#include "shaders/terrainShader.hpp"
#include "object.hpp"
#include "terrain.hpp"

#include <list>

namespace marrow {
    class Renderer {
        private:
            const glm::vec3 _fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
            const float _fogDensity = 0.1;
            TerrainShader _terrain_shader;
            ObjectShader _object_shader;
            //SkyboxShader _skybox_shader;
            glm::mat4 _projectionMatrix;
            std::list<Object *> _objectList;
            std::list<Light *> _lightList;
            Terrain * _terrain = NULL;
            //Skybox _skybox;

        public:
            Renderer();

            void addObject(Object * newObject);
            void addLight(Light * newLight);
            void addTerrain(Terrain * newTerrain);
            void render(Camera & camera);
    };
}

#endif
