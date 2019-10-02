//
// Created by max on 19/07/19.
//

#include <Global.h>

#include "../include/Global.h"

using namespace TE;
bool Global::debug;
GraphicsAPI Global::activeAPI;
float Global::timedUpdateInterval = 1;

unsigned int Global::maxSimultaneousLights = 5;

bool Global::GetDebugState() {
    return debug;
}

GraphicsAPI Global::GetActiveAPI() {
    return activeAPI;
}

unsigned int Global::GetMaxSimultaneousLightsCount() {
    return maxSimultaneousLights;
}
