#ifndef MARROW_RENDERER_H
#define MARROW_RENDERER_H

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
            Skybox _skybox;

        public:
            Renderer() {
                _terrain_shader = TerrainShader();
                _object_shader = ObjectShader();
                _projectionMatrix = glm::glm::perspective(glm::radians(45.0f), float(glutGet(GLUT_WINDOW_WIDTH)) / float(glutGet(GLUT_WINDOW_HEIGHT)), 0.1f, 100.0f);
                _objectList = std::list<Object>();
            }

            addObject(Object * newObject) {
                _objectList.push_back(newObject);
            }

            render(Camera & camera) {
                _object_shader.set();
                _object_shader.setFogColor(_fogColor);
                _object_shader.setFogDensity(_fogDensity);
    };
}

#endif
