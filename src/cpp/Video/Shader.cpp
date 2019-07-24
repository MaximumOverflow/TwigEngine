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

TE::Shader* TE::Shader::Create(std::string vertexSource, std::string fragmentSource)
{
    Shader* shader;
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL shader...");
            shader = new GL_Shader(vertexSource.c_str(), fragmentSource.c_str());
            break;
#endif

        default:
            Debug::Log("Failed to create shader due to unimplemented API functions", Debug::Severity::Error);
            break;
    }
    return shader;
}

TE::Shader *TE::Shader::CreateFromFile(std::string vertexPath, std::string fragmentPath) {
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

    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL shader...");
            shader = new GL_Shader(cVertexSrc, cFragmentSrc);
            break;
#endif

        default:
            Debug::Log("Failed to create shader due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return shader;
}

int TE::Shader::GetUniformFromCache(std::string name) {
    auto uniform = uniformCache.find(name);
    if (uniform == uniformCache.end())
        return -1;
    return uniformCache[name];
}

void TE::Shader::AddUniformToCache(std::string name, int id) {
    uniformCache[name] = id;
}
