//
// Created by max on 19/09/25.
//

#include "Audio/AudioManager.h"
#include "Debug.h"

using namespace TE;

ALCdevice* AudioManager::device;
ALCcontext* AudioManager::context;

#define RETRIEVE_ALC_ERROR  {\
                            Debug::Log("OpenAL return error of type " + Get_AL_Error(), Debug::Severity::Error);\
                            return;\
                            }

std::string AudioManager::Get_AL_Error() {
    auto error = alGetError();
    switch (error)
    {
        case AL_INVALID_NAME:       return "INVALID NAME";
        case AL_INVALID_ENUM:       return "INVALID ENUM";
        case AL_INVALID_VALUE:      return "INVALID VALUE";
        case AL_INVALID_OPERATION:  return "INVALID OPERATION";
        case AL_OUT_OF_MEMORY:      return "OUT OF MEMORY";
        default:                    return "UNKNOWN ERROR";
    }
}

void AudioManager::Init() {
    device = alcOpenDevice(nullptr);
    if (!device)    RETRIEVE_ALC_ERROR;

    context = alcCreateContext(device, nullptr);
    if (!context)                           RETRIEVE_ALC_ERROR
    if (!alcMakeContextCurrent(context))    RETRIEVE_ALC_ERROR
}

void AudioManager::Terminate() {
    alcCloseDevice(device);
    alcDestroyContext(context);
}
