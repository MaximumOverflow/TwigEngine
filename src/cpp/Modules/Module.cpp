//
// Created by max on 22/07/19.
//
#include "Objects/GameObjects/GameObject.h"
#include "Modules/Module.h"
using namespace TE;

TE::GameObject* TE::Module::GetParent() {
    return parent;
}
