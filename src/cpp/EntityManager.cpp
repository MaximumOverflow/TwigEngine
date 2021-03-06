//
// Created by max on 21/07/19.
//

#include <algorithm>
#include <EntityManager.h>

#include "../include/EntityManager.h"
#include "../include/Debug.h"

using namespace TE;

std::vector<GameObject*> EntityManager::entities;

void TE::EntityManager::AddEntity(GameObject *entity) {
    Debug::Log("Added GameObject \"" + entity->name + "\" to entity list");
    entities.push_back(entity);
}

void EntityManager::RemoveEntity(GameObject *entity) {
    Debug::Log("Removed GameObject \"" + entity->name + "\" from entity list");
    auto e = std::find(entities.begin(), entities.end(), entity);
    entities.erase(e);
}

void EntityManager::UpdateAll() {
    for (auto& entity : entities)
    {
        if (!entity->enabled) return;
        entity->Update();
        entity->UpdateModules();
    }
}

void EntityManager::UpdateAllTimed() {
    for (auto& entity : entities)
    {
        if (!entity->enabled) return;

        entity->TimedUpdate();
    }
}
