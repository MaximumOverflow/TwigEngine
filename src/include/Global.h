//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GLOBAL_H
#define TWIG_ENGINE_GLOBAL_H

#include "Types/Types.h"

namespace TE {
    struct Global {
        static bool Debug;
        static GraphicsAPI activeAPI;
        static float timedUpdateInterval;
    };
}



#endif //TWIG_ENGINE_GLOBAL_H
