//
// Created by max on 19/09/25.
//

#ifndef TWIG_ENGINE_AUDIOBUFFER_H
#define TWIG_ENGINE_AUDIOBUFFER_H

#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace TE {
    class AudioBuffer {
    private:
        unsigned int ID;
        ALsizei size, freq;
        ALenum format;
        ALvoid *data;
        ALboolean loop = AL_FALSE;

    public:
        AudioBuffer();
        AudioBuffer(std::string path);
        ~AudioBuffer();

        void LoadSound(std::string path);
    };
}

#endif //TWIG_ENGINE_AUDIOBUFFER_H
