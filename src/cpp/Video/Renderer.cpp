//
// Created by max on 18/07/19.
//

#include "Video/Renderer.h"
#include "Debug.h"
#include "Global.h"
#include "Modules/MeshRenderer.h"

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
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace TE;
#define activeAPI Global::activeAPI
Window* Renderer::window;
Shader* Renderer::defaultShader;
std::vector<Camera*> Renderer::cameras;

std::string defaultVertex {"#version 330 core\n"
                           "\n"
                           "layout (location = 0) in vec3 vertex_pos;\n"
                           "\n"
                           "uniform mat4 te_projection, te_view, te_model;"
                           "void main()\n"
                           "{\n"
                           "    vec4 pos = (te_projection * te_view * te_model) * vec4(vertex_pos, 1.0);"
                           "    gl_Position = pos;\n"
                           "}"};

std::string defaultFragment {"#version 330 core\n"
                             "\n"
                             "out vec4 color;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "   color = vec4(1, 1, 1, 1.0);\n"
                             "}"};

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
    defaultShader = Shader::Create(defaultVertex, defaultFragment);
    defaultShader->Bind();
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
            window = new GL_Window(width, height, title);
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
    for (auto& camera : cameras)
    {
        if (!camera->enabled) return;
            camera->Bind();

#ifndef TE_PLATFORM_MACOS
        if (activeAPI == GraphicsAPI::OpenGL)
        {
            VAO->Bind();

            defaultShader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
            defaultShader->SetUniformMat4f("te_view", camera->GetTransformMatrix());
            defaultShader->SetUniformMat4f("te_model", Mat4(1.f));

            glDrawElements(GL_TRIANGLES, VAO->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
        }
#endif
    }
}

void Renderer::Draw(GameObject *gameObject) {
    for (auto& camera : cameras)
    {
        if (!camera->enabled) return;
            camera->Bind();

        MeshRenderer* meshRenderer = gameObject->GetModule<MeshRenderer>();
        VertexArrayObject* vao = meshRenderer->GetMeshVAO();
        Shader* shader = meshRenderer->GetShader();

        Transform* view = camera->GetModule<Transform>();
        Transform* transform = gameObject->GetModule<Transform>();

        vao->Bind();

#ifndef TE_PLATFORM_MACOS
        if (activeAPI == GraphicsAPI::OpenGL)
        {
            if (shader != nullptr)
            {
                shader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
                shader->SetUniformMat4f("te_view", view->GetTransformMatrix());
                if (transform != nullptr)
                    shader->SetUniformMat4f("te_model", transform->GetTransformMatrix());
                else
                    shader->SetUniformMat4f("te_model", Mat4());
            }
            else
            {
                defaultShader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
                defaultShader->SetUniformMat4f("te_view", camera->GetTransformMatrix());
                if (transform != nullptr)
                    defaultShader->SetUniformMat4f("te_model", transform->GetTransformMatrix());
                else
                    defaultShader->SetUniformMat4f("te_model", Mat4());
            }
            glDrawElements(GL_TRIANGLES, vao->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
        }
#endif
    }
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

void Renderer::AddCamera(Camera *camera) {
    cameras.push_back(camera);
    Debug::Log("Added camera \"" + camera->name + "\"");
}

void Renderer::RemoveCamera(Camera *camera) {
    auto index = std::find(cameras.begin(), cameras.end(), camera);
    cameras.erase(index);
    Debug::Log("Removed camera \"" + camera->name + "\"");
}
