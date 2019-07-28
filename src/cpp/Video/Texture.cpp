//
// Created by max on 28/07/19.
//

#include "Global.h"
#include "Debug.h"
#include "Video/Texture.h"

#ifndef TE_PLATFORM_MACOS
    #include "Video/GL/GL_Texture.h"
#endif

TE::Texture *TE::Texture::Create(const std::string path) {
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            return new GL_Texture(path);
#endif
        default:
            Debug::Log("Failed to create texture due to unimplemented API functions", Debug::Severity::Error);
            return nullptr;
    }
}
