//
// Created by max on 22/07/19.
//
#include "Video/VertexArrayObject.h"
#include "Global.h"
#include "Debug.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_VertexArrayObject.h"
#endif


TE::VertexArrayObject *TE::VertexArrayObject::Create() {
    VertexArrayObject* VAO = nullptr;
    switch (Global::GetActiveAPI())
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL VAO...");
            VAO = new GL_VertexArrayObject();
            break;
#endif
        default:
            Debug::Log("Failed to create Vertex Array Object due to unimplemented API functions", Debug::Severity::Error);
            break;
    }
    return VAO;
}
