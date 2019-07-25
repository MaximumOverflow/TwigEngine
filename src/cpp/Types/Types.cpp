//
// Created by max on 21/07/19.
//
#include <Types/Types.h>

#include "Types/Types.h"
#include "Global.h"

unsigned int TE::LookupType(DataType type) {
#ifndef TE_PLATFORM_MACOS
    if (Global::GetActiveAPI() == GraphicsAPI::OpenGL)
        return (unsigned int) 0x1400+type;
#endif

    return 0;
}

unsigned int TE::StructureSize(TE::DataStructure dataStructure, TE::DataType dataType) {
    unsigned int dataSize = 0;
    switch (dataType)
    {
        case TE_BYTE:               dataSize = 1; break;
        case TE_UNSIGNED_BYTE:      dataSize = 1; break;
        case TE_SHORT:              dataSize = 2; break;
        case TE_UNSIGNED_SHORT:     dataSize = 2; break;
        case TE_INT:                dataSize = 4; break;
        case TE_UNSIGNED_INT:       dataSize = 4; break;
        case TE_FLOAT:              dataSize = 4; break;
        case TE_2_BYTES:            dataSize = 2; break;
        case TE_3_BYTES:            dataSize = 3; break;
        case TE_4_BYTES:            dataSize = 4; break;
        case TE_DOUBLE:             dataSize = 8; break;
        default: return 0;
    }
    switch (dataStructure)
    {
        case DataStructure::TE_VEC1:    return dataSize;
        case DataStructure::TE_VEC2:    return dataSize*2;
        case DataStructure::TE_VEC3:    return dataSize*3;
        case DataStructure::TE_VEC4:    return dataSize*4;
        case DataStructure::TE_MAT4:    return dataSize*16;
        default: return 0;
    }
}
