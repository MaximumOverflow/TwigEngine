//
// Created by max on 19/09/25.
//

#include "AudioBuffer.h"

using namespace TE;

AudioBuffer::AudioBuffer() {
    alGenBuffers(1, &ID);
}

AudioBuffer::AudioBuffer(std::string path) {
    alGenBuffers(1, &ID);
}

AudioBuffer::~AudioBuffer() {
    alDeleteBuffers(1, &ID);
}