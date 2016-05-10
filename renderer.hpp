#ifndef MARROW_RENDERER_H
#define MARROW_RENDERER_H

#include "camera.hpp"
#include "shaders/objectShader.hpp"
#include "shaders/terrainShader.hpp"
#include "shaders/skyboxShader.hpp"
#include "shaders/waterShader.hpp"
#include "object.hpp"
#include "terrain.hpp"
#include "skybox.hpp"
#include "frame.hpp"
#include "water.hpp"

#include <list>
#include <map>

namespace marrow {
    class Renderer {
        private:
            int _w, _h;
            const glm::vec3 _fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
            const float _fogDensity = 0.1;
            TerrainShader _terrain_shader;
            ObjectShader _object_shader;
            SkyboxShader _skybox_shader;
            WaterShader _water_shader;
            glm::mat4 _projectionMatrix;
            std::list<Object *> _objectList;
            std::list<Light *> _lightList;
            std::map<std::pair<GLint, GLint>, Terrain * > _terrainList;
            std::list<Water *> _waterList;
            Skybox * _skybox = NULL;
            float _water_level = 0.0f;
            Frame * _frame = NULL;

        public:
            Renderer();

            void addObject(Object * newObject);
            void addLight(Light * newLight);
            void addTerrain(std::pair<GLint, GLint> offset, Terrain * newTerrain);
            void addWater(Water * newWater);
            void setSkybox(Skybox * skybox);
            void setWaterLevel(float water_level);
            void basic_render(Camera & camera, glm::vec4 clip_plane);
            void render(Camera & camera);
    };
}

#endif
