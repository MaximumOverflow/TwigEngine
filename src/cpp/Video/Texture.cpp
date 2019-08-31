//
// Created by max on 28/07/19.
//

#include <Video/Texture.h>

#include "Global.h"
#include "Debug.h"
#include "Video/Texture.h"

#ifndef TE_PLATFORM_MACOS
    #include "Video/GL/GL_Texture.h"
#endif

using namespace TE;

std::shared_ptr<Texture> Texture::Create(const std::string path, bool retainBuffer) {
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            return std::make_shared<GL_Texture>(path);
#endif
        default:
            Debug::Log("Failed to create texture due to unimplemented API functions", Debug::Severity::Error);
            return nullptr;
    }
}

std::shared_ptr<Texture> Texture::Create(const unsigned char *buffer, int width, int height, int bpp) {
    Debug::Log("Textures created by external buffer references will not retain the buffer's data", Debug::Severity::Warning);
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            return std::make_shared<GL_Texture>(buffer, width, height, bpp);
#endif
        default:
            Debug::Log("Failed to create texture due to unimplemented API functions", Debug::Severity::Error);
            return nullptr;
    }
}
