//
// Created by max on 18/07/19.
//

#ifndef TWIG_ENGINE_RENDERER_H
#define TWIG_ENGINE_RENDERER_H

#include <vector>
#include <string>

#include "Window.h"
#include "VertexArrayObject.h"

#ifndef TE_PLATFORM_MACOS
    #include <GLFW/glfw3.h>
#endif

namespace TE {
    enum class GraphicsAPI {
#ifndef TE_PLATFORM_MACOS
        OpenGL, Vulkan,
#endif

#ifdef TE_PLATFORM_WINDOWS
        DirectX,
#endif

#ifdef TE_PLATFORM_MACOS
        Metal
#endif
    };

    class Renderer {
    private:
        static GraphicsAPI activeAPI;
        static Window* window;

        static Window* CreateWindow(unsigned int width, unsigned int height, std::string title);

        static std::vector<VertexArrayObject*> VAOs;
    public:
        static int Init(GraphicsAPI API);
        static int Init(GraphicsAPI API, unsigned int width, unsigned int height, std::string title);
        static void Terminate();

        static void UseGraphicsAPI(GraphicsAPI API);
        static GraphicsAPI GetCurrentAPI();
        static bool WindowIsOpen();
        static void Run();

        static VertexArrayObject* CreateVertexArrayObject();
    };
}


#endif //TWIG_ENGINE_RENDERER_H
