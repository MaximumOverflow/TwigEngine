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
    VertexArrayObject* VAO;
    switch (Global::activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL VAO...");
            VAO = new GL_VertexArrayObject();
            break;
#endif
        default:
            Debug::Log("Failed to create Vertex Array Object due to undefined API implementation.", Debug::Severity::Error);
            break;
    }
    return VAO;
}
