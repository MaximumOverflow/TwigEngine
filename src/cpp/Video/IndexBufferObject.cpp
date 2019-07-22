//
// Created by max on 22/07/19.
//


#include "Global.h"
#include "Debug.h"
#include "Video/IndexBufferObject.h"

#ifndef TE_PLATFORM_MACOS
#include "Video/GL/GL_IndexBufferObject.h"
#endif

TE::IndexBufferObject *TE::IndexBufferObject::Create() {
    IndexBufferObject* IBO;
    switch (Global::activeAPI)
    {
#ifndef TE_PLATFORM_MACOS
        case GraphicsAPI::OpenGL:
            Debug::Log("Creating OpenGL IBO...");
            IBO = new GL_IndexBufferObject();
            break;
#endif

        default:
            Debug::Log("Failed to create Index Buffer Object due to unimplemented API functions", Debug::Severity::Error);
            break;
    }
    return IBO;
}

