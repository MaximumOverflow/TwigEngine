//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_ENTITYMANAGER_H
#define TWIG_ENGINE_ENTITYMANAGER_H

#include "Objects/GameObjects/GameObject.h"

#include <vector>

namespace TE {
    class EntityManager {
    private:
        static std::vector<GameObject*> entities;
    public:
        static void AddEntity(GameObject* entity);
        static void RemoveEntity(GameObject* entity);

        static void UpdateAll();
    };
}

#endif //TWIG_ENGINE_ENTITYMANAGER_H
