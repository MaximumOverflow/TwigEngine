//
// Created by max on 22/07/19.
//
#include <fstream>
#include <Video/Shader.h>


#include "Video/Shader.h"
#include "Global.h"
#include "Debug.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_Shader.h"
#endif

using namespace TE;

std::shared_ptr<Shader> TE::Shader::Create(std::string vertexSource, std::string fragmentSource)
{
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL shader...");
            return std::make_shared<GL_Shader>(vertexSource.c_str(), fragmentSource.c_str());
#endif

        default:
            Debug::Log("Failed to create shader due to unimplemented API functions", Debug::Severity::Error);
            return nullptr;
    }
}

std::shared_ptr<Shader> TE::Shader::CreateFromFile(std::string vertexPath, std::string fragmentPath) {
    Shader* shader;

    std::string vertexSrc, fragmentSrc, tmp;
    std::ifstream file;

    file.open(vertexPath);
    if (!file.is_open())
    {
        Debug::Log("Failed to open vertex shader", Debug::Severity::Error);
        return nullptr;
    }
    while (std::getline(file, tmp))
        vertexSrc.append(tmp).append("\n");
    file.close();

    file.open(fragmentPath);
    if (!file.is_open())
    {
        Debug::Log("Failed to open fragment shader", Debug::Severity::Error);
        return nullptr;
    }
    while (std::getline(file, tmp))
        fragmentSrc.append(tmp).append("\n");
    file.close();

    const char *cVertexSrc = vertexSrc.c_str(), *cFragmentSrc = fragmentSrc.c_str();

    return Create(vertexSrc, fragmentSrc);
}

int TE::Shader::GetUniformFromCache(std::string name) {
    if (uniformCache.find(name) == uniformCache.end())
        return -5;
    return uniformCache[name];
}

void TE::Shader::AddUniformToCache(std::string name, int id) {
    Debug::Log("Adding \"" + name + "\" to uniform cache...");
    uniformCache[name] = id;
}
