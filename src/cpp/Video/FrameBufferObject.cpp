//
// Created by max on 22/07/19.
//

#include "Debug.h"
#include "Video/FrameBufferObject.h"
#include "Global.h"
using namespace TE;

#ifndef TE_PLATFORM_MACOS
    #include "Video/GL/GL_FrameBufferObject.h"
#endif

FrameBufferObject* FrameBufferObject::Create(float width, float height) {
    FrameBufferObject* FBO;
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            FBO = new GL_FrameBufferObject();
            FBO->SetResolution(width, height);
            return FBO;
#endif

        default:
            Debug::Log("Failed to create Frame Buffer Object due to unimplemented API functions", Debug::Severity::Error);
            return nullptr;
    }
}
