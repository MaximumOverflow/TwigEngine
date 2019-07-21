//
// Created by max on 21/07/19.
//
#include "../../include/Types/Types.h"
#include "../../include/Global.h"

unsigned int TE::LookupType(Type type) {
#ifndef TE_PLATFORM_MACOS
    if (Global::activeAPI == GraphicsAPI::OpenGL)
        return (unsigned int) 0x1400+type;
#endif

    return 0;
}
