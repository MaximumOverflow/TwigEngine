//
// Created by max on 21/07/19.
//

#include <algorithm>

#include "Objects/GameObject.h"
#include "EntityManager.h"
#include "Debug.h"

TE::GameObject::GameObject() {
    EntityManager::AddEntity(this);
}

TE::GameObject::~GameObject() {
    Debug::Log("Deleting modules for GameObjects \"" + name + "\"..." );
    for (auto& module : modules)
        delete module;

    modules.clear();

    EntityManager::RemoveEntity(this);
}

void TE::GameObject::UpdateModules() {
    for (auto& module : modules)
        module->Update();
}

void TE::GameObject::RemoveModule(TE::Module *module) {
    auto i = std::find(modules.begin(), modules.end(), module);
    modules.erase(i);
}
