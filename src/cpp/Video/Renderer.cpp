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
    #include "Video/GL/GL_Texture.h"
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

std::vector<GameObject*> Renderer::renderQueue;
std::unordered_map<Mesh*, std::vector<MeshRenderer*>> Renderer::renderQueue3D;

Shader* Renderer::defaultShader = nullptr;
std::string Renderer::defaultVertex;
std::string Renderer::defaultFragment;
Texture* Renderer::defaultTexture;

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

    const unsigned char* texBuffer = new unsigned char[4*4] {
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
    };
    defaultTexture = Texture::Create(texBuffer, 2,2,4);
    delete[] texBuffer;
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
    renderQueue.push_back(gameObject);
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
            "out vec2 te_frag_texture_position;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   vec4 pos = (te_projection * te_view * te_model) * vec4(te_position, 1.0);\n"
            "   gl_Position = pos;\n"
            "   te_frag_position = vec3(te_model * vec4(te_position, 1.0));\n"
            "   te_frag_normal = vec3(transpose(inverse(mat3(te_model))) * te_normal);\n"
            "   te_frag_texture_position = te_texture_position;\n"
            "}"
    };

    defaultFragment = {
            "#version 330 core\n"
            "\n"
            "in vec3 te_frag_normal, te_frag_position;\n"
            "in vec2 te_frag_texture_position;\n"
            "uniform vec3 te_light_position[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "uniform vec4 te_light_color[" + std::to_string(Global::maxSimultaneousLights) + "];\n"
            "uniform sampler2D te_texture_slot;\n"
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
            "       float distance = abs(distance(te_light_position[i], te_frag_position));"
            "       "
            "       vec3 lightDir = normalize(te_light_position[i] - te_frag_position);\n"
            "       light += (te_light_color[i] * dot(normal, lightDir) * te_light_color[i].w) / distance ;\n"
            "   }\n"
            "   vec4 textureColor = texture(te_texture_slot, te_frag_texture_position);\n"
            "   color = vec4((textureColor * light).xyz, 1.0);\n"
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

void Renderer::SetMaximumSimultaneousLights(unsigned int lightCount) {
    Global::maxSimultaneousLights = lightCount;
    CompileDefaultShader();
}

void Renderer::DrawQueue() {
    for (auto& camera : cameras)
    {
        if (!camera->enabled)
            return;

        camera->Bind();

        Clear();
        auto* cameraTransform = camera->GetModule<Transform>();

        for (auto& gameObject : renderQueue)
        {
            auto* gameObjectTransform = gameObject->GetModule<Transform>();
            auto* meshRenderer = gameObject->GetModule<MeshRenderer>();
            VertexArrayObject* vao = meshRenderer->GetMeshVAO();
            Shader* shader = meshRenderer->GetShader();
            Texture* texture = meshRenderer->GetTexture();
            vao->Bind();

            if (glm::distance(gameObjectTransform->GetPosition(), cameraTransform->GetPosition()) > (meshRenderer->customDrawDistance != 0 ? meshRenderer->customDrawDistance : camera->drawDistance))
                continue;

            if (shader != nullptr)
            {
                shader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
                shader->SetUniformMat4f("te_view", camera->GetTransformMatrix());
                shader->SetUniformMat4f("te_model", gameObjectTransform->GetTransformMatrix());

                if (texture != nullptr)
                {
                    texture->Bind();
                    #ifndef TE_PLATFORM_MACOS
                    if (activeAPI == GraphicsAPI::OpenGL)
                        shader->SetUniformVec1i("te_texture_slot", ((GL_Texture*) texture)->GetSlot());
                    #endif
                }
                else
                {
                    defaultTexture->Bind();
                    #ifndef TE_PLATFORM_MACOS
                    if (activeAPI == GraphicsAPI::OpenGL)
                        shader->SetUniformVec1i("te_texture_slot", 0);
                    #endif
                }
            }
            else
            {
                defaultShader->SetUniformMat4f("te_projection", camera->GetProjectionMatrix());
                defaultShader->SetUniformMat4f("te_view", camera->GetTransformMatrix());
                defaultShader->SetUniformMat4f("te_model", gameObjectTransform->GetTransformMatrix());

                if (texture != nullptr)
                {
                    texture->Bind();
                    #ifndef TE_PLATFORM_MACOS
                    if (activeAPI == GraphicsAPI::OpenGL)
                        defaultShader->SetUniformVec1i("te_texture_slot", ((GL_Texture*) texture)->GetSlot());
                    #endif
                }
                else
                {
                    defaultTexture->Bind();
                    #ifndef TE_PLATFORM_MACOS
                    if (activeAPI == GraphicsAPI::OpenGL)
                        defaultShader->SetUniformVec1i("te_texture_slot", 0);
                    #endif
                }
            }

            unsigned int i = 0;

            for (auto& light : lights)
            {
                if (i > Global::maxSimultaneousLights) break;

                auto* lightTransform = light->GetModule<Transform>();

                auto lightPos = lightTransform->GetPosition();
                if (glm::distance(gameObjectTransform != nullptr? gameObjectTransform->GetPosition() : Vec3(0,0,0), lightPos) < light->drawDistance)
                {
                    if (shader != nullptr)
                    {
                        shader->SetUniformVec3f("te_light_position[" + std::to_string(i) + "]", lightPos);
                        shader->SetUniformVec4f("te_light_color[" + std::to_string(i) + "]", light->color);
                    }
                    else
                    {
                        defaultShader->SetUniformVec3f("te_light_position[" + std::to_string(i) + "]", lightPos);
                        defaultShader->SetUniformVec4f("te_light_color[" + std::to_string(i) + "]", light->color);
                    }
                    i++;
                }
            }


            #ifndef TE_PLATFORM_MACOS
            if (activeAPI == GraphicsAPI::OpenGL)
            {
                glDrawElements(wireframe ? GL_LINES : GL_TRIANGLES, vao->GetIndexBufferObjectElementCount(), GL_UNSIGNED_INT, 0);
            }
            #endif

        }

        camera->Unbind();
    }

    renderQueue.clear();
}

void Renderer::Draw(Mesh* mesh, MeshRenderer* meshRenderer) {
    //Todo Implement instanced rendering
    auto queueEntry = renderQueue3D.find(mesh);
    if (queueEntry == renderQueue3D.end())
    {
        renderQueue3D[mesh] = std::vector<MeshRenderer*>();
        std::vector<MeshRenderer*>& meshRendererVector = renderQueue3D[mesh];
        meshRendererVector.push_back(meshRenderer);
    }
    else {
        std::vector<MeshRenderer*>& meshRendererVector = renderQueue3D[mesh];
        meshRendererVector.push_back(meshRenderer);
    }
}

void Renderer::DrawQueueInstanced() {
    for (auto& pair : renderQueue3D)
    {
        Mesh* mesh = pair.first;
        mesh->GetVAO()->Bind();
    }
}
