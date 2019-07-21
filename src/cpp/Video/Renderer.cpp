//
// Created by max on 18/07/19.
//

#include "../../include/Video/Renderer.h"
#include "../../include/Debug.h"
#include "../../include/Memory.h"
#include "../../include/Global.h"

#ifndef TE_PLATFORM_MACOS
#include "../../include/Video/GL/GL_Window.h"
#include "../../include/Video/VK/VK_Window.h"
#include "../../include/Video/GL/GL_VertexArrayObject.h"
#include "../../include/Video/GL/GL_VertexBufferObject.h"
#include "../../include/Video/GL/GL_IndexBufferObject.h"
#include "../../include/Video/GL/GL_Shader.h"
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

void Renderer::Run() {
#ifndef TE_PLATFORM_MACOS
    if (activeAPI == GraphicsAPI::OpenGL)
    {
        GL_Window* gl_window = static_cast<GL_Window*>(window);
        glClear(GL_COLOR_BUFFER_BIT);
        //Rendering code
        for (auto& VAO : Cache::Graphics::VAOs)
        {
            VAO->Bind();
            if (VAO->HasIndexBufferObject())
            {
                glDrawElements(GL_TRIANGLES, VAO->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
            }
        }
        //
        gl_window->SwapBuffers();
    }
#endif
}

bool Renderer::WindowIsOpen() {
    return window->IsOpen();
}

std::shared_ptr<VertexArrayObject> Renderer::CreateVertexArrayObject() {
    std::shared_ptr<VertexArrayObject>VAO;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL VAO...");
            VAO = std::make_shared<GL_VertexArrayObject>(Cache::Graphics::VAOs.size());
            Cache::Graphics::VAOs.push_back(VAO);
            break;
#endif
        default:
            Debug::Log("Failed to create Vertex Array Object due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return VAO;
}

std::shared_ptr<VertexBufferObject> Renderer::CreateVertexBufferObject() {
    std::shared_ptr<VertexBufferObject> VBO;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL VBO...");
            VBO = std::make_shared<GL_VertexBufferObject>(Cache::Graphics::VBOs.size());
            Cache::Graphics::VBOs.push_back(VBO);
            break;
#endif
        default:
            Debug::Log("Failed to create Vertex Buffer Object due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return VBO;
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

std::shared_ptr<Shader> Renderer::CreateShader(const std::string vertexPath, const std::string fragmentPath) {
    std::shared_ptr<Shader> shader;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL shader...");
            shader = std::make_shared<GL_Shader>(vertexPath, fragmentPath);
            break;
#endif

        default:
            Debug::Log("Failed to create shader due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return shader;
}

std::shared_ptr<Shader> Renderer::CreateShader(const char *vertexSrc, const char *fragmentSrc) {
    std::shared_ptr<Shader> shader;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL shader...");
            shader = std::make_shared<GL_Shader>(vertexSrc, fragmentSrc);
            break;
#endif

        default:
            Debug::Log("Failed to create shader due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return shader;
}

std::shared_ptr<IndexBufferObject> Renderer::CreateIndexBufferObject() {
    std::shared_ptr<IndexBufferObject> IBO;
    switch (activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL IBO...");
            IBO = std::make_shared<GL_IndexBufferObject>();
            break;
#endif

        default:
            Debug::Log("Failed to create Index Buffer Object due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return IBO;
}

const Window *Renderer::GetWindow() {
    return window;
}
