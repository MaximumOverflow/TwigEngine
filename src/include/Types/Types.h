//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_TYPES_H
#define TWIG_ENGINE_TYPES_H

#include <glm/glm.hpp>

#define BIT(x) (1<<x)

namespace TE {
    enum class GraphicsAPI {
#ifndef TE_PLATFORM_MACOS
        OpenGL, Vulkan,
#endif

#ifdef TE_PLATFORM_WINDOWS
        DirectX,
#endif

#ifdef TE_PLATFORM_MACOS
        Metal
#endif
    };

    enum class EventType {
        WindowClose, WindowResize, WindowMinimize, WindowMaximize,
        MouseButtonPress, MouseButtonRelease, MouseButtonHold, MouseMove, MouseScroll,
        KeyPress, KeyRelease, KeyHold,
    };

    enum EventCategory {
        WindowEvent = BIT(1),
        MouseEvent = BIT(2),
        KeyboardEvent = BIT(3)
    };

    enum DataType {
        TE_BYTE,
        TE_UNSIGNED_BYTE,
        TE_SHORT,
        TE_UNSIGNED_SHORT,
        TE_INT,
        TE_UNSIGNED_INT,
        TE_FLOAT,
        TE_2_BYTES,
        TE_3_BYTES,
        TE_4_BYTES,
        TE_DOUBLE
    };

    unsigned int LookupType(DataType type);

    enum class DataStructure {
        TE_VEC1,
        TE_VEC2,
        TE_VEC3,
        TE_VEC4,
        TE_MAT4,
    };

    unsigned int StructureSize(DataStructure dataStructure, DataType dataType);

    enum class FileType {
        OBJ
    };

    enum class ProjectionMode {
        Ortho, Perspective
    };

    typedef glm::vec1 Vec1;
    typedef glm::vec2 Vec2;
    typedef glm::vec3 Vec3;
    typedef glm::vec4 Vec4;
    typedef glm::mat4 Mat4;

    struct Color {
        float r, g, b, a;
        Color(float r, float g, float b, float a = 1) : r(r), g(g), b(b), a{a} {};
    };
}


#endif //TWIG_ENGINE_TYPES_H
