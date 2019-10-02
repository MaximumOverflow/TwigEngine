//
// Created by max on 18/07/19.
//

#include "Video/Renderer.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "Global.h"
#include "Modules/MeshRenderer.h"
#include "Layers/RenderingLayer.h"
#include "Layers/LayerStack.h"

#include "InternalShaders/DefaultDiffuse.h"
#include "InternalShaders/DefaultFlat.h"


#ifndef TE_PLATFORM_MACOS
    #include "Video/GL/API_OpenGL.h"
    #include "Video/VK/API_Vulkan.h"
#endif

#include <exception>
#include <stdexcept>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Video/Renderer.h>


using namespace TE;
std::unique_ptr<RenderingAPI> Renderer::activeAPI;

bool Renderer::wireframe;

std::vector<Camera*> Renderer::cameras;
std::vector<Light*> Renderer::lights;

std::vector<GameObject*> Renderer::renderQueue;
std::unordered_map<Mesh*, std::vector<MeshRenderer*>> Renderer::renderQueue3D;

std::shared_ptr<Shader> Renderer::defaultShader = nullptr;
std::shared_ptr<Texture> Renderer::defaultTexture;

int Renderer::Init(GraphicsAPI API) {
    Debug::Log("Initializing renderer...");

    LayerStack::AddLayer(new RenderingLayer());

    Global::activeAPI = API;
    switch (API)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            activeAPI = std::make_unique<API_OpenGL>();
            break;

        case GraphicsAPI::Vulkan:
            Debug::Log("Vulkan support is still under development. Some features might be missing or misbehave.", Debug::Severity::Warning);
            activeAPI = std::make_unique<API_Vulkan>();
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
    SetSwapInterval(1);
    RecompileInternalShaders();

    const unsigned char* texBuffer = new unsigned char[4*4] {
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
            255, 255, 255, 255,
    };
    defaultTexture = Texture::Create(texBuffer, 2,2,4);
    delete[] texBuffer;

    RecompileInternalShaders();
    defaultShader = ResourceManager::GetAsset<Shader>("DefaultDiffuse");
    return 0;
}

std::shared_ptr<Window> Renderer::CreateWindow(unsigned int width, unsigned int height, std::string title) {
    return activeAPI->CreateWindow(width, height, title);
}

void Renderer::Draw(GameObject *gameObject) {
    renderQueue.push_back(gameObject);
}


bool Renderer::HasOpenWindows() {
    return activeAPI->GetWindowCount() > 0;
}

void Renderer::Clear() {
    activeAPI->Clear();
}

void Renderer::SwapBuffers() {
    activeAPI->SwapBuffers();
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

void Renderer::RecompileInternalShaders() {
    auto diffuse = s_DefaultDiffuse();
    ResourceManager::AddAsset("DefaultDiffuse", Shader::Create(diffuse.first, diffuse.second));

    auto flat = s_DefaultFlat();
    ResourceManager::AddAsset("DefaultFlat", Shader::Create(flat.first, flat.second));
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
    RecompileInternalShaders();
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
            pShader shader = meshRenderer->GetShader();
            pTexture texture = meshRenderer->GetTexture();

            if (!vao)
            {
                Debug::Log("Gameobject \""+ gameObject->name +"\" doesn't have a valid VAO", Debug::Severity::Error);
                continue;
            }

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
                    shader->SetUniformVec1i("te_texture_slot", texture->GetSlot());
                }
                else
                {
                    defaultTexture->Bind();
                    shader->SetUniformVec1i("te_texture_slot", 0);
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
                    defaultShader->SetUniformVec1i("te_texture_slot", texture->GetSlot());
                }
                else
                {
                    defaultTexture->Bind();
                    defaultShader->SetUniformVec1i("te_texture_slot", 0);
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

            activeAPI->DrawIndexed(wireframe, vao->GetIndexBufferObjectElementCount());
        }

        camera->Unbind();
    }

    renderQueue.clear();
}

std::shared_ptr<Window> Renderer::GetActiveWindow() {
    return activeAPI->GetCurrentWindow();
}

void Renderer::UpdateCameraProjections() {
    for (auto& camera : cameras)
        camera->UpdateProjection();
}

void Renderer::SetDefaultShader(std::shared_ptr<Shader> shader) {
    defaultShader = shader;
}

void Renderer::ClearQueue() {
    renderQueue.clear();
}

