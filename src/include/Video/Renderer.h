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
#include "Objects/Mesh.h"
#include "Modules/MeshRenderer.h"
#include "Objects/GameObjects/Camera.h"
#include "Objects/GameObjects/Light.h"
#include "RenderingAPI.h"

namespace TE {
    class Renderer {
        friend class GL_Window;
    private:
        static std::shared_ptr<Window> CreateWindow(unsigned int width, unsigned int height, std::string title);
        static std::unique_ptr<RenderingAPI> activeAPI;

        static std::vector<Camera*> cameras;
        static std::vector<Light*> lights;
        static std::vector<GameObject*> renderQueue;

        static std::unordered_map<Mesh*, std::vector<MeshRenderer*>> renderQueue3D;

        static std::shared_ptr<Shader> defaultShader;
        static std::shared_ptr<Texture> defaultTexture;
        static std::string defaultVertex, defaultFragment;
        static void CompileDefaultShader();
    public:
        static int Init(GraphicsAPI API);
        static int Init(GraphicsAPI API, unsigned int width, unsigned int height, std::string title);
        static const std::unique_ptr<RenderingAPI>& GetActiveAPI() { return activeAPI; }

        static bool HasOpenWindows();
        static std::shared_ptr<Window> GetActiveWindow();
        static void BindDefaultShader() { defaultShader->Bind(); };

        static void AddCamera(Camera* camera);
        static void RemoveCamera(Camera* camera);

        static void AddLight(Light* light);
        static void RemoveLight(Light* light);
        static void SetMaximumSimultaneousLights(unsigned int lightCount);
        static void Draw(GameObject* gameObject);
        static void DrawQueue();
        static void Clear();
        static void SwapBuffers();
        static void SetSwapInterval(short interval);
        static bool wireframe;
    };
}


#endif //TWIG_ENGINE_RENDERER_H
