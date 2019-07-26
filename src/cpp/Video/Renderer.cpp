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
#include <Video/Renderer.h>


using namespace TE;
#define activeAPI Global::activeAPI
Window* Renderer::window;
bool Renderer::wireframe;

std::vector<Camera*> Renderer::cameras;
std::vector<Light*> Renderer::lights;

Shader* Renderer::defaultShader = nullptr;
std::string Renderer::defaultVertex;
std::string Renderer::defaultFragment;

int Renderer::Init(GraphicsAPI API) {
    Debug::Log("Initializing renderer...");
    Global::activeAPI = API;
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
    CompileDefaultShader();
    return 0;
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

            BindDefaultShader();

#ifndef TE_PLATFORM_MACOS
        if (activeAPI == GraphicsAPI::OpenGL)
        {
            VAO->Bind();

            defaultShader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
            defaultShader->SetUniformMat4f("te_view", camera->GetTransformMatrix());
            defaultShader->SetUniformMat4f("te_model", Mat4(1.f));

            glDrawElements(wireframe ? GL_LINES : GL_TRIANGLES, VAO->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
        }
#endif
    }
}

void Renderer::Draw(GameObject *gameObject) {

    MeshRenderer* meshRenderer = gameObject->GetModule<MeshRenderer>();
    VertexArrayObject* vao = meshRenderer->GetMeshVAO();
    Shader* shader = meshRenderer->GetShader();
    Transform* transform = gameObject->GetModule<Transform>();
    vao->Bind();


    for (auto& camera : cameras)
    {
        if (!camera->enabled) return;
            camera->Bind();

        Transform* view = camera->GetModule<Transform>();

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

        unsigned short i = 0;

        for (auto& light : lights)
        {
            auto* lightTransform = light->GetModule<Transform>();

            if (transform != nullptr && i < Global::maxSimultaneousLights)
            {
                auto pos = lightTransform->GetPosition();
                if (glm::distance(transform->GetPosition(), pos) < 200){
                    if (shader != nullptr)
                    {
                        shader->SetUniformVec3f("te_light_position[" + std::to_string(i) + "]", pos);
                        shader->SetUniformVec4f("te_light_color[" + std::to_string(i) + "]", light->color);
                    }
                    else
                    {
                        defaultShader->SetUniformVec3f("te_light_position[" + std::to_string(i) + "]", pos);
                        defaultShader->SetUniformVec4f("te_light_color[" + std::to_string(i) + "]", light->color);
                    }
                    i++;
                }
            }
        }

#ifndef TE_PLATFORM_MACOS
        if (activeAPI == GraphicsAPI::OpenGL)
        {
            glDrawElements(wireframe ? GL_LINES : GL_TRIANGLES, vao->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Renderer::SetSwapInterval(short interval) {
    switch (Global::GetActiveAPI()) {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
        case GraphicsAPI::Vulkan:
            glfwSwapInterval(interval);
            break;
#endif
    }
}

void Renderer::CompileDefaultShader() {
    defaultVertex = {
            "#version 330 core\n"
            "\n"
            "layout (location = 0) in vec3 te_position;\n"
            "layout (location = 1) in vec2 te_texture_position;\n"
            "layout (location = 2) in vec3 te_normal;\n"
            "\n"
            "uniform mat4 te_projection, te_view, te_model;\n"
            "uniform vec3 te_light_position[" + std::to_string(Global::maxSimultaneousLights) + "]\n;"
            "uniform vec4 te_light_color[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "\n"
            "out vec3 te_frag_normal, te_frag_position;\n"
            "out vec3 te_frag_light_position[" + std::to_string(Global::maxSimultaneousLights) + "]; \n"
            "out vec4 te_frag_light_color[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "\n"
            "void main()\n"
            "{\n"
            "   vec4 pos = (te_projection * te_view * te_model) * vec4(te_position, 1.0);\n"
            "   gl_Position = pos;\n"
            "   te_frag_position = (te_model * vec4(te_position, 1.0)).xyz;\n"
            "   te_frag_normal = te_normal;\n"
            "   for (int i = 0; i < " + std::to_string(Global::maxSimultaneousLights) + "; i++)\n"
            "   {\n"
            "       te_frag_light_position[i] = te_light_position[i];\n"
            "       te_frag_light_color[i] = te_light_color[i];\n"
            "   }\n"
            "}"
    };

    defaultFragment = {
            "#version 330 core\n"
            "\n"
            "in vec3 te_frag_normal, te_frag_position;\n"
            "in vec3 te_frag_light_position[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "in vec4 te_frag_light_color[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "\n"
            "out vec4 color;\n"
            "\n"
            "vec3 normal = normalize(te_frag_normal);\n"
            "\n"
            "vec4 light;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   for (int i = 0; i < " + std::to_string(Global::maxSimultaneousLights) + "; i++)\n"
            "   {\n"
            "       float distance = abs(distance(te_frag_light_position[i], te_frag_position)) / 20;"
            "       "
            "       vec3 lightDir = normalize(te_frag_light_position[i] - te_frag_position);\n"
            "       light += te_frag_light_color[i] / distance  * max(dot(normal, lightDir),0.0f);\n"
            "   }\n"
            "   color = light;\n"
            "}"
    };
    delete defaultShader;
    defaultShader = Shader::Create(defaultVertex, defaultFragment);
}

void Renderer::AddLight(Light *light) {
    lights.push_back(light);
    Debug::Log("Added light \"" + light->name + "\"");
}

void Renderer::RemoveLight(Light *light) {
    auto index = std::find(lights.begin(), lights.end(), light);
    lights.erase(index);
    Debug::Log("Removed camera \"" + light->name + "\"");
}
