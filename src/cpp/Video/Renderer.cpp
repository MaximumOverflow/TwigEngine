//
// Created by max on 18/07/19.
//

#include "../../include/Video/Renderer.h"
#include "../../include/Debug.h"

#ifndef TE_PLATFORM_MACOS
    #include "../../include/Video/GL/GL_Window.h"
    #include "../../include/Video/VK/VK_Window.h"
    #include "../../include/Video/GL/GL_VertexArrayObject.h"
#endif

#include <exception>
#include <stdexcept>

using namespace TE;
GraphicsAPI Renderer::activeAPI;
Window* Renderer::window;
std::vector<VertexArrayObject*> Renderer::VAOs;

int Renderer::Init(GraphicsAPI API) {
    Debug::Log("Initializing renderer...");
    UseGraphicsAPI(API);
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Initializing GLFW...");
            if (!glfwInit())
                return -1;
            break;

        case GraphicsAPI::Vulkan:
            Debug::Log("Vulkan support is still under development. Some features might be missing or misbehave.", Debug::Severity::Warning);
            Debug::Log("Initializing GLFW...");
            if (!glfwInit())
                return -1;
            break;
#endif
        default:
            return -5;
    }
    return -1;
}

int Renderer::Init(GraphicsAPI API, unsigned int width, unsigned int height, std::string title) {
    Init(API);
    CreateWindow(width, height, std::move(title));
    return 0;
}

void Renderer::UseGraphicsAPI(GraphicsAPI API) {
    activeAPI = API;
}

Window* Renderer::CreateWindow(unsigned int width, unsigned int height, std::string title) {
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating new OpenGL window...");
            window = new GL_Window(width, height, std::move(title));
            return window;

        case GraphicsAPI::Vulkan:
            Debug::Log("Creating new Vulkan window...");
            window = new VK_Window(width, height, title);
#endif

#ifdef TE_PLATFORM_WINDOWS

#endif

#ifdef TE_PLATFORM_MACOS

#endif

        default:
            return nullptr;
    }
}

void Renderer::Run() {
#ifndef TE_PLATFORM_MACOS
    if (activeAPI == GraphicsAPI::OpenGL)
    {
        GL_Window* gl_window = static_cast<GL_Window*>(window);
        glClear(GL_COLOR_BUFFER_BIT);
        //Rendering code

        //
        gl_window->SwapBuffers();
    }
#endif
}

bool Renderer::WindowIsOpen() {
    return window->IsOpen();
}

VertexArrayObject* Renderer::CreateVertexArrayObject() {
    VertexArrayObject* VAO;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            VAO = new GL_VertexArrayObject(VAOs.size());
            VAOs.push_back(VAO);
            break;
#endif
    }
    return VAO;
}

GraphicsAPI Renderer::GetCurrentAPI() {
    return activeAPI;
}

void Renderer::Terminate() {
    delete window;
    if (activeAPI == GraphicsAPI::OpenGL || activeAPI == GraphicsAPI::Vulkan)
    {
        glfwTerminate();
    }
}
