//
// Created by max on 18/07/19.
//

#include "Video/Renderer.h"
#include "Debug.h"
#include "Global.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_Window.h"
#include "Video/VK/VK_Window.h"
#include "Video/GL/GL_VertexArrayObject.h"
#include "Video/GL/GL_VertexBufferObject.h"
#include "Video/GL/GL_IndexBufferObject.h"
#include "Video/GL/GL_Shader.h"
#endif

#include <exception>
#include <stdexcept>


using namespace TE;
#define activeAPI Global::activeAPI
Window* Renderer::window;

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
            glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
            return window;

        case GraphicsAPI::Vulkan:
            Debug::Log("Creating new Vulkan window...");
            window = new VK_Window(width, height, title);
            return window;
#endif

#ifdef TE_PLATFORM_WINDOWS

#endif

#ifdef TE_PLATFORM_MACOS

#endif

        default:
            return nullptr;
    }
}

void Renderer::Draw(VertexArrayObject* VAO) {
#ifndef TE_PLATFORM_MACOS
    if (activeAPI == GraphicsAPI::OpenGL)
    {
        VAO->Bind();
        glDrawElements(GL_TRIANGLES, VAO->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
    }
#endif
}

bool Renderer::WindowIsOpen() {
    return window->IsOpen();
}

GraphicsAPI Renderer::GetCurrentAPI() {
    return activeAPI;
}

void Renderer::Terminate() {
    delete window;
#ifndef TE_PLATFORM_MACOS
    if (activeAPI == GraphicsAPI::OpenGL || activeAPI == GraphicsAPI::Vulkan)
    {
        glfwTerminate();
    }
#endif
}

const Window *Renderer::GetWindow() {
    return window;
}

void Renderer::Clear() {
#ifndef TE_PLATFORM_MACOS
    if (activeAPI == GraphicsAPI::OpenGL)
        glClear(GL_COLOR_BUFFER_BIT);
#endif
}

void Renderer::SwapBuffers() {
#ifndef TE_PLATFORM_MACOS
    if (Global::activeAPI == GraphicsAPI::OpenGL) {
        GL_Window *gl_window = static_cast<GL_Window *>(window);
        gl_window->SwapBuffers();
    }
#endif
}
