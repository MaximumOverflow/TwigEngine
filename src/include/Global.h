//
// Created by max on 19/07/19.
//

#ifndef TWIG_ENGINE_GLOBAL_H
#define TWIG_ENGINE_GLOBAL_H

#include "Types/Types.h"

namespace TE {
    class Global {
        friend class Application;
        friend class Renderer;
        friend class Debug;
    private:
        static bool debug;
        static GraphicsAPI activeAPI;
        static float timedUpdateInterval;

        static unsigned int maxSimultaneousLights;
    public:
        static bool GetDebugState();
        static const GraphicsAPI& GetActiveAPI();
    };
}



#endif //TWIG_ENGINE_GLOBAL_H
