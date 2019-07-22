//
// Created by max on 21/07/19.
//

#ifndef TWIG_ENGINE_MODULE_H
#define TWIG_ENGINE_MODULE_H

#include <string>

#include "Objects/GameObjects/GameObject.h"

namespace TE {
    class Module {
    private:
        GameObject* parent;
    public:
        Module(GameObject* parent) : parent{parent} {};
        GameObject* GetParent();
        virtual void Update() {};
    };
}
#endif //TWIG_ENGINE_MODULE_H
