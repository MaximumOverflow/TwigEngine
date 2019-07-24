//
// Created by max on 21/07/19.
//
#include "Types/Types.h"
#include "Global.h"

unsigned int TE::LookupType(DataType type) {
#ifndef TE_PLATFORM_MACOS
    if (Global::GetActiveAPI() == GraphicsAPI::OpenGL)
        return (unsigned int) 0x1400+type;
#endif

    return 0;
}
