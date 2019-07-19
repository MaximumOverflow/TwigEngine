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

#ifndef TE_PLATFORM_MACOS
    #include <GLFW/glfw3.h>
#endif

namespace TE {
    class Renderer {
    private:
        static Window* window;

        static Window* CreateWindow(unsigned int width, unsigned int height, std::string title);
    public:
        static int Init(GraphicsAPI API);
        static int Init(GraphicsAPI API, unsigned int width, unsigned int height, std::string title);
        static void Terminate();

        static void UseGraphicsAPI(GraphicsAPI API);
        static GraphicsAPI GetCurrentAPI();
        static bool WindowIsOpen();
        static void Run();

        static std::shared_ptr<VertexArrayObject> CreateVertexArrayObject();
        static std::shared_ptr<VertexBufferObject>  CreateVertexBufferObject();
    };
}


#endif //TWIG_ENGINE_RENDERER_H
