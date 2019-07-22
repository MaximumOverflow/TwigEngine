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
        static const Window* GetWindow();

        static void Draw(VertexArrayObject* VAO);
        static void Clear();
        static void SwapBuffers();
    };
}


#endif //TWIG_ENGINE_RENDERER_H
