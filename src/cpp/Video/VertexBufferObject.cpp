//
// Created by max on 22/07/19.
//

#include "Video/VertexBufferObject.h"
#include "Debug.h"
#include "Global.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_VertexBufferObject.h"
#endif

TE::VertexBufferObject* TE::VertexBufferObject::Create() {
    VertexBufferObject* VBO;
    switch (Global::activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL VBO...");
            VBO = new GL_VertexBufferObject();
            break;
#endif
        default:
            Debug::Log("Failed to create Vertex Buffer Object due to unimplemented API functions", Debug::Severity::Error);
            break;
    }
    return VBO;
}

