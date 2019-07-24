//
// Created by max on 19/07/19.
//

#include "../include/Global.h"

using namespace TE;
bool Global::debug;
GraphicsAPI Global::activeAPI;
float Global::timedUpdateInterval = 1;

bool Global::GetDebugState() {
    return debug;
}

const TE::GraphicsAPI &Global::GetActiveAPI() {
    return activeAPI;
}