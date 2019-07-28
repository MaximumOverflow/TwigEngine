//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_RENDERER_H
#define TWIG_ENGINE_RENDERER_H
#pragma once

#include <vector>
#include <string>

#include "Window.h"
#include "VertexArrayObject.h"
#include "IndexBufferObject.h"
#include "Shader.h"
#include "Objects/GameObjects/Camera.h"
#include "Objects/GameObjects/Light.h"

namespace TE {
    class Renderer {
    private:
        static Window* window;
        static Window* CreateWindow(unsigned int width, unsigned int height, std::string title);

        static std::vector<Camera*> cameras;
        static std::vector<Light*> lights;

        static Shader* defaultShader;
        static std::string defaultVertex, defaultFragment;
        static void CompileDefaultShader();
    public:
        static int Init(GraphicsAPI API);
        static int Init(GraphicsAPI API, unsigned int width, unsigned int height, std::string title);
        static void Terminate();

        static GraphicsAPI GetCurrentAPI();
        static bool WindowIsOpen();
        static const Window* GetWindow();
        static void BindDefaultShader() { defaultShader->Bind(); };

        static void AddCamera(Camera* camera);
        static void RemoveCamera(Camera* camera);

        static void AddLight(Light* light);
        static void RemoveLight(Light* light);
        static void SetMaximumSimultaneousLights(unsigned int lightCount);

        static void Draw(VertexArrayObject* VAO);
        static void Draw(GameObject* gameObject);
        static void Clear();
        static void SwapBuffers();
        static void SetSwapInterval(short interval);
        static bool wireframe;
    };
}


#endif //TWIG_ENGINE_RENDERER_H
