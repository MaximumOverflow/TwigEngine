//
// Created by max on 19/09/25.
//

#ifndef TWIG_ENGINE_AUDIOMANAGER_H
#define TWIG_ENGINE_AUDIOMANAGER_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>

namespace TE {
    class AudioManager {
    private:
        static ALCdevice* device;
        static ALCcontext* context;

    public:
        static void Init();
        static void Terminate();
        static std::string Get_AL_Error();
    };
}

#endif //TWIG_ENGINE_AUDIOMANAGER_H
